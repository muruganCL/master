<?php

/**
 * Check availability.
 */
function lulzbot_store_ajax_availability() {
  // $countries = json_decode(file_get_contents(drupal_get_path('module', 'lulzbot_store') . '/countries.json'));
  // $country_keys = array_keys((array) $countries->countries);

  // product
  $node = NULL;
  if (isset($_GET['p'])) {
    $path = drupal_lookup_path('source', $_GET['p']);
    if (!$path) {
      drupal_not_found();
      drupal_exit();
    }
  }

  $cache_key = 'availability_' . md5($path);
  $cache = cache_get($cache_key, 'cache_store');
  if ($cache && stools_use_cache($cache)) {
    drupal_add_http_header('X-Store-Cache', 1);
    drupal_json_output($cache->data);
    return;
  }

  if ($path) {
    $node = menu_get_object('node', 1, $path);
  }
  if (!$node) {
    drupal_not_found();
    drupal_exit();
  }

  // get the products from this node
  $products = stools_field_value($node, 'field_product_reference');
  $product_availability = array();

  foreach ($products as $product) {
    $product_availability[$product['product_id']] = lulzbot_store_product_availability($product['sku']);
  }

  cache_set($cache_key, $product_availability, 'cache_store', time() + variable_get('lulzbot_store_ajax_availability_expire', 600));
  drupal_json_output($product_availability);
}

/**
 * Check what countries the product is available in.
 *
 * Country availability is calculated by checking the product status in the
 * warehouses and the country-to-warehouse configuration.
 *
 * Options:
 *
 * - cache: set to TRUE/FALSE if this call should be cached. Defaults to cache
 *          enabled.
 *
 * @param string $sku
 *   The product SKU.
 * @param array $options
 *   Optional optoins list.
 *
 * @return array
 *   An array of the product availability per country.
 */
function lulzbot_store_product_availability($sku, array $options = array()) {
  $countries = array();

  $shipwire = shipwire_api_request();
  if (!isset($options['cache']) || (isset($options['cache']) && $options['cache'])) {
    $shipwire->cacheable();
  }

  // request the stock
  try {
    $response = $shipwire->debug()->stock(array('sku' => $sku));
  }
  catch (Exception $e) {
    return $countries;
  }

  if (!$response) {
    drupal_set_message(t('There was an error receiving product availability. Please check back soon.'), 'error');
  }
  if ($response && !$response->isError()) {
    foreach ($response->resource->items as $item) {
      $warehouse_countries = lulzbot_store_warehouse_country_codes($item->resource->warehouseRegion);
      foreach ($warehouse_countries as $warehouse_country) {
        if (!isset($countries[$warehouse_country])) {
          $countries[$warehouse_country] = 0;
        }
        $countries[$warehouse_country] += $item->resource->good;
      }
    }
  }

  if ($override_availability = variable_get('lulzbot_store_availability', FALSE)) {
    if (isset($override_availability[$sku])) {
      if (user_access('access devel information')) {
        static $show_override_message = TRUE;
        if ($show_override_message) {
          drupal_set_message(t('Using overriden availability settings.'));
          $show_override_message = FALSE;
        }
      }
      $countries = $override_availability[$sku];
    }
  }

  return $countries;
}

/**
 * Return the country codes using a warehouse.
 *
 * @param string $warehouse
 *   Warehouse location code.
 *
 * @return array
 *   An array of country codes that use the requested warehouse.
 */
function lulzbot_store_warehouse_country_codes($warehouse) {
  static $warehouses = array();

  if (empty($warehouses) || !isset($warehouses[$warehouse])) {
    $warehouse_results = db_select('lulzbot_store_countries', 'c')
      ->fields('c', array('country_code'))
      ->condition('warehouses', '%' . db_like($warehouse) . '%', 'LIKE')
      ->execute();

    $warehouses[$warehouse] = array();
    while ($result = $warehouse_results->fetchAssoc()) {
      $warehouses[$warehouse][] = $result['country_code'];
    }
  }

  return $warehouses[$warehouse];
}

/**
 * Send a product availability notification.
 */
function lulzbot_store_send_notification($email, $skus, &$context) {
  // load the products
  $products = array();
  foreach ($skus as $sku) {
    // casting this to a string as it seems to complain otherwise
    $products[(string) $sku] = commerce_product_load_by_sku($sku);
  }

  $result = drupal_mail('lulzbot_store', 'product_availability', $email, language_default(), array('products' => $products));
  if (isset($result['result'])) {
    // change the status of the users' notifications
    db_query('UPDATE lulzbot_store_notify SET sent=1, notified=:now WHERE mail=:email AND sku IN (:skus)', array(':now' => time(), ':email' => $email, ':skus' => $skus));
    return;
  }

  watchdog('lulzbot_store', 'Unable to send the product availability notification to %email for: %skus ', array('%email' => $email, '%skus' => $skus), WATCHDOG_ERROR);
}

/**
 * The product availability notification batch has finished.
 */
function lulzbot_store_notifications_finished($success, $results, $operations) {
}

/**
 * Determine if a product sku is available in a country.
 *
 * @param string $sku
 *   The SKU for the product.
 * @param string $country
 *   The country code to lookup.
 * @param array $options
 *   Optional options to pass to the availability check. See lulzbot_store_product_availability().
 *
 * @return bool
 *   TRUE if the product is available in that country. FALSE if not.
 */
function lulzbot_store_product_is_available($sku, $country, array $options = array()) {
  $availability = lulzbot_store_product_availability($sku, $options);
  if (isset($availability[$country]) && $availability[$country] > 0) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Check if a product variant is available.
 */
function lulzbot_store_product_variant_is_available($nid, $field, $tid, $country) {
  // get the products referenced by this node
  $products = db_query('SELECT p.field_product_reference_product_id FROM node n
    JOIN field_data_field_product_reference p ON p.entity_id=n.nid AND p.revision_id AND n.vid
    WHERE n.nid=:nid', array(':nid' => $nid))->fetchCol();

  if ($products) {
    $limit_query = db_select('field_data_' . $field, 'f');
    $limit_query
      ->condition('entity_id', $products, 'IN')
      ->condition($field . '_tid', $tid, '=');
    $limit_query->join('commerce_product', 'p', 'p.product_id=f.entity_id AND p.revision_id=f.revision_id');
    $limit_query->fields('p', array('sku'));
    $limited_products = $limit_query->execute()->fetchCol();
    if ($limited_products) {
      foreach ($limited_products as $product) {
        if (lulzbot_store_product_is_available($product, $country)) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

/**
 * Get the available colors.
 */
function lulzbot_store_available_filament_colors($nid) {
  module_load_include('inc', 'lulzbot_store');
  $location = lulzbot_store_user_country();
  // if there is no location yet, there are no available colors.
  if (!$location) {
    return array();
  }

  $colors = db_query('SELECT c.field_product_filament_colors_tid, n.nid, :location AS location FROM node n
    JOIN field_data_field_product_reference pr ON pr.entity_id=n.nid AND pr.revision_id=n.vid
    JOIN field_data_field_product_filament_colors c ON c.entity_id=pr.field_product_reference_product_id
    JOIN commerce_product cp ON cp.product_id=c.entity_id AND cp.revision_id=c.revision_id
    WHERE n.nid=:nid GROUP BY c.field_product_filament_colors_tid', array(':nid' => $nid, ':location' => $location))->fetchAllAssoc('field_product_filament_colors_tid');

  $colors = array_filter($colors, 'lulzbot_store_filter_filament_colors');
  return $colors;
}

/**
 * Get the available colors mapped to SKUs.
 */
function lulzbot_store_available_filament_color_sku_map($nid) {
  module_load_include('inc', 'lulzbot_store');

  $colors = db_query('SELECT c.field_product_filament_colors_tid, cp.sku FROM node n
    JOIN field_data_field_product_reference pr ON pr.entity_id=n.nid AND pr.revision_id=n.vid
    JOIN field_data_field_product_filament_colors c ON c.entity_id=pr.field_product_reference_product_id
    JOIN commerce_product cp ON cp.product_id=c.entity_id AND cp.revision_id=c.revision_id
    WHERE n.nid=:nid GROUP BY c.field_product_filament_colors_tid', array(':nid' => $nid))->fetchAllAssoc('field_product_filament_colors_tid');

  $map = array();
  foreach ($colors as $color) {
    if (!isset($map[$color->field_product_filament_colors_tid])) {
      $map[$color->field_product_filament_colors_tid] = array();
    }

    $map[$color->field_product_filament_colors_tid][] = $color->sku;
  }
  return $map;
}

/**
 * Filter the available colors.
 */
function lulzbot_store_filter_filament_colors($color) {
  return lulzbot_store_product_variant_is_available($color->nid, 'field_product_filament_colors', $color->field_product_filament_colors_tid, $color->location);
}

/**
 * Check quantity availability.
 */
function lulzbot_store_product_quantity_is_available($sku, $country, $quantity, array $options = array()) {
  $availability = lulzbot_store_product_availability($sku, $options);
  $quantity = intval($quantity);
  if (isset($availability[$country]) && $availability[$country] >= $quantity) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Return an error message about availability.
 */
function lulzbot_store_availability_message($product, $quantity, $country) {
  $availability = lulzbot_store_product_availability($product->sku);
  $products = format_plural($availability[$country], 'item', 'items');
  $is = format_plural($availability[$country], 'is', 'are');
  return t('You have requested %quantity %product %products, but there !is only !available available.', array('%quantity' => intval($quantity), '!available' => $availability[$country], '%product' => $product->title, '%products' => $products, '!is' => $is));
}
