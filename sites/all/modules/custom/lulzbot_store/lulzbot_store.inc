<?php
/**
 * Set the location cookie.
 */
function lulzbot_store_ajax_set_location() {
  $cookie = lulzbot_store_cookie_name();
  $location = $_GET['location'];
  $response = array('status' => 1, 'is_available' => 0, 'availability' => array(), 'related_availability' => array());

  $countries = lulzbot_store_get_countries();
  if (in_array($location, array_keys($countries))) {
    setcookie($cookie, $location, strtotime('+1 year'), '/');
    $_SESSION[$cookie] = $location;

    if (isset($_GET['product_id'])) {
      module_load_include('inc', 'lulzbot_store', 'lulzbot_store.availability');
      $product_id = intval($_GET['product_id']);
      $product = commerce_product_load($product_id);
      if ($product) {
        $countries = lulzbot_store_product_availability($product->sku);
        if (isset($countries[$location]) && $countries[$location]) {
          $response['is_available'] = 1;
          $response['availability'] = $countries[$location];
        }

        // find products also used on the display node(s) this product is used
        // in... and then figure out the availability of the related items.
        $related_products = lulzbot_store_find_related_products($product);
        foreach ($related_products as $related_product) {
          $countries = lulzbot_store_product_availability($related_product['sku']);
          $response['related_availability'][$related_product['sku']] = $countries;
        }
      }
    }
  }
  drupal_json_output($response);
}

/**
 * Add an notification entry for this product.
 */
function lulzbot_store_ajax_notify_me() {
  $message = array();

  // accept only POST requests
  if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    drupal_add_http_header('Status', '400 Invalid Request');
    $message['status'] = 'error';
    $message['error'] = 'Invalid request';
    drupal_json_output($message);
    drupal_exit();
  }

  // validate the form token
  if (!drupal_valid_token($_POST['form_token'])) {
    drupal_add_http_header('Status', '403 Forbidden');
    $message['status'] = 'error';
    $message['error'] = 'Invalid token';
    drupal_json_output($message);
    drupal_exit();
  }

  if (!isset($_POST['notify_me'], $_POST['product_id'])) {
    drupal_add_http_header('Status', '400 Invalid Request');
    $message['status'] = 'error';
    $message['error'] = 'Invalid request.';
    drupal_json_output($message);
    drupal_exit();
  }

  // only do stuff if the notify is set.
  if (isset($_POST['notify_me']) && valid_email_address($_POST['notify_me'])) {
    $product = commerce_product_load(intval($_POST['product_id']));
    if (!$product) {
      drupal_add_http_header('Status', '404 Not Found');
      $message['status'] = 'error';
      $message['error'] = 'Could not find product.';
      drupal_json_output($message);
      drupal_exit();
    }

    // check if there is already a notification in place.
    $exists = db_query('SELECT * FROM lulzbot_store_notify WHERE mail=:mail AND sku=:sku AND sent=0', array(
      'mail' => check_plain($_POST['notify_me']),
      'sku' => $product->sku,
    ));
    if ($exists->rowCount() <= 0) {
      db_insert('lulzbot_store_notify')
        ->fields(array(
          'id' => NULL,
          'mail' => check_plain($_POST['notify_me']),
          'sku' => $product->sku,
          'requested' => time(),
          'notified' => 0,
          'country' => lulzbot_store_user_country(),
        ))
        ->execute();
    }

    // save this to the session
    $_SESSION['lulzbot_store_email'] = check_plain($_POST['notify_me']);

    $message['status'] = 'ok';
    $message['notify_me'] = check_plain($_POST['notify_me']);
    drupal_json_output($message);
    drupal_exit();
  }

  $message['status'] = 'error';
  drupal_json_output($message);
}

/**
 * Clear the user's stored location cookie.
 */
function lulzbot_store_clear_location_page() {
  lulzbot_store_delete_location_cookie();
  drupal_set_message(t('The location cookie has been removed'));
  drupal_goto('');
}

/**
 * Return the cookie name.
 */
function lulzbot_store_cookie_name() {
  return variable_get('lulzbot_store_location_cookie', 'lulzbot_store_location');
}

/**
 * Return an array of countries.
 */
function lulzbot_store_get_countries($all = FALSE) {
  $config = lulzbot_store_get_countries_config();
  $options = _addressfield_country_options_list();
  $country_options = array();
  foreach ($options as $country_code => $country) {
    if (!in_array($country_code, array_keys($config))) {
      // this country does not exist in the config yet.
      $config[$country_code] = lulzbot_store_get_default_country_settings($country_code, $country);

      // save it
      db_insert('lulzbot_store_countries')
        ->fields(array(
          'country_code' => $country_code,
          'name' => $country,
          'hidden' => $config[$country_code]['hidden'],
          'warehouses' => $config[$country_code]['warehouses'],
        ))
        ->execute();
      $country_options[$country_code] = $country;
      continue;
    }

    if ($all || (!$all && !$config[$country_code]->hidden)) {
      $country_options[$country_code] = $config[$country_code]->name;
    }
  }

  return $country_options;
}

/**
 * Return an array of countries that get free shipping.
 */
function lulzbot_store_get_free_countries() {
  $free_countries = explode(',', variable_get('lulzbot_store_free_countries', ''));
  return array_filter($free_countries);
}

/**
 * Load the countries config.
 */
function lulzbot_store_get_countries_config() {
  static $config;
  if (!$config) {
    $config = db_select('lulzbot_store_countries', 'c')
      ->fields('c')
      ->execute()
      ->fetchAll();

    $new_config = array();
    foreach ($config as $country) {
      $new_config[$country->country_code] = $country;
    }
    $config = $new_config;
  }
  return $config;
}

/**
 * Default settings for a country.
 */
function lulzbot_store_get_default_country_settings($country_code, $name) {
  return array(
    'code' => $country_code,
    'name' => $name,
    'hidden' => 0,
    'warehouses' => 'CHI,LAX',
  );
}

/**
 * Get the user's email.
 */
function lulzbot_store_get_user_email() {
  global $user;

  // if we have a session variable with the email, use that.
  if (isset($_SESSION['lulzbot_store_email'])) {
    return $_SESSION['lulzbot_store_email'];
  }

  // if the user is anonymous, we don't have an email.
  if (user_is_anonymous()) {
    return;
  }

  // return the user's saved email.
  return $user->mail;
}

/**
 * Check if the user has a location cookie set.
 *
 * Uses a mix of session and cookie here because cookies don't behave well with
 * the AJAX requests, but sessions do.
 *
 * @return mixed
 *   Returns the cookie value or FALSE if there is not cookie.
 */
function lulzbot_store_user_has_location_cookie() {
  $cookie = lulzbot_store_cookie_name();
  $cookie_value = NULL;
  if (isset($_COOKIE[$cookie])) {
    $cookie_value = $_COOKIE[$cookie];
  }

  if (!$cookie_value && isset($_SESSION[$cookie])) {
    $cookie_value = $_SESSION[$cookie];
  }

  $_SESSION[$cookie] = $_COOKIE[$cookie] = $cookie_value;
  return $_COOKIE[$cookie];
}

/**
 * Check if the user has a saved shipping location.
 */
function lulzbot_store_user_has_saved_address() {
  global $user;
  $default = commerce_addressbook_get_default_profile_id($user->uid, 'shipping');
  if ($default) {
    return commerce_customer_profile_load($default);
  }
  return FALSE;
}

/**
 * Delete the location cookie.
 */
function lulzbot_store_delete_location_cookie() {
  $cookie = lulzbot_store_cookie_name();
  setcookie($cookie, '', time() - 100, '/');
  if (isset($_SESSION)) {
    unset($_SESSION[$cookie]);
  }
}

/**
 * Get the user location.
 *
 * @return mixed
 *   Either the user's country as a string (no saved address), or an address
 *   when they have one saved in the addressbook.
 */
function lulzbot_store_user_location() {
  // if the user is anonymous, they only have a location saved if there is a
  // location cookie.
  if (user_is_anonymous()) {
    // check if they have a location cookie
    if ($location = lulzbot_store_user_has_location_cookie()) {
      return $location;
    }
    return FALSE;
  }

  // if the user is authenticated they may either have a cookie or maybe they
  // have a saved shipping profile with commerce_addressbook.
  if ($location = lulzbot_store_user_has_location_cookie()) {
    return $location;
  }

  return lulzbot_store_user_has_saved_address();
}

/**
 * Return just the country.
 */
function lulzbot_store_user_country() {
  $location = lulzbot_store_user_location();
  if (!is_string($location)) {
    if (isset($location->commerce_customer_address, $location->commerce_customer_address[LANGUAGE_NONE]) && count($location->commerce_customer_address[LANGUAGE_NONE]) > 0) {
      $location = $location->commerce_customer_address[LANGUAGE_NONE][0]['country'];
    }
  }
  return $location;
}

/**
 * Check if the user has a notification for this product.
 */
function lulzbot_store_user_has_notification_for_product($product, $email) {
  if (!$email) {
    return FALSE;
  }

  $exists = db_query('SELECT * FROM lulzbot_store_notify WHERE mail=:mail AND sku=:sku AND sent=0', array(':mail' => $email, ':sku' => $product->sku));
  if ($exists->rowCount() > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Delete everything in the store cache.
 */
function lulzbot_store_clear_all_cache() {
  db_delete('cache_store')
    ->execute();
}

/**
 * Delete all product cache for the given path.
 */
function lulzbot_store_clear_product_cache($path) {
  db_delete('cache_store')
    ->condition('name', '%' . db_like('_' . $path), 'LIKE')
    ->execute();
}

/**
 * Get the country that this order is shipping to.
 *
 * @param object $order
 *   A Commerce order.
 *
 * @return string
 *   The country code from the shipping address.
 */
function lulzbot_store_get_order_country($order, array $options = array()) {
  static $orders = array();

  if (!isset($orders[$order->order_number]) || (isset($orders[$order->order_number]) && isset($options['reset']))) {
    $profile = stools_field_value($order, 'commerce_customer_shipping', LANGUAGE_NONE, array('key' => 'profile_id'));
    $profile = commerce_customer_profile_load($profile);
    $address = stools_field_value($profile, 'commerce_customer_address');
    $orders[$order->order_number] = $address['country'];
  }

  return $orders[$order->order_number];
}

/**
 * Return the warehouse(s) for a Commerce order.
 *
 * @param object $order
 *   A Commerce order.
 *
 * @return array
 *   An array of country codes from the shipping address or FALSE if there
 *   isn't one.
 */
function lulzbot_store_get_shipwire_warehouses_for_order($order) {
  $country = lulzbot_store_get_order_country($order);
  $countries = lulzbot_store_get_countries_config();

  if (!isset($countries[$country])) {
    return FALSE;
  }

  // get the list of warehouses for this country
  return explode(',', $countries[$country]->warehouses);
}

/**
 * Get the line item objects for this order.
 */
function lulzbot_store_get_order_line_items($order) {
  $line_items = stools_field_value($order, 'commerce_line_items', LANGUAGE_NONE, array('key' => 'line_item_id'));
  if (!$line_items) {
    return FALSE;
  }
  if (!is_array($line_items)) {
    $line_items = array($line_items);
  }
  // var_dump($line_items);
  commerce_line_item_load_multiple($line_items);

  // figure out which line items are products
  $results = array();
  foreach ($line_items as $line_item_id) {
    $line_item = commerce_line_item_load($line_item_id);
    if (stools_field_has_value($line_item, 'commerce_product')) {
      $results[] = $line_item;
    }
  }
  return $results;
}

/**
 * Get and add the shipping code to a decorated orded.
 */
function lulzbot_store_add_line_items_ship_codes($decorated_order) {
  $commerce_order = $decorated_order['commerce_order'];

  $shipping_code = shipwire_api_get_shipping_code_from_order($commerce_order);

  // get the Shipwire warehouses
  $add_shipping_codes = function ($line_items) use ($commerce_order, $shipping_code) {
    if ($shipping_code === 'LULZBOT_STORE_FREE_SHIPPING') {
      // the user gets free shipping for this order, but we still need to send a
      // valid shipping service level over with the orders. To get this, we will
      // send rate requests for each shipwire order.
      $profile = stools_field_value($commerce_order, 'commerce_customer_shipping', LANGUAGE_NONE, array('key' => 'profile_id'));
      $profile = commerce_customer_profile_load($profile);

      $rates = shipwire_api_get_default_rates_for_order($commerce_order, $profile, $line_items);

      $api = shipwire_api_request();
      $response = $api->post()->rate($rates[0]);

      if ($response->isError() || !isset($response->resource->rates)) {
        watchdog('lulzbot_store', 'Unable to get shipping rates for this free shipping order', array(), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
      }
      else {
        $cost = NULL;
        $code = NULL;
        foreach ($response->resource->rates as $rate) {
          foreach ($rate->serviceOptions as $service_option) {
            $total = 0;
            foreach ($service_option->shipments as $shipment) {
              $total += $shipment->cost->amount;
            }
            if ($cost === NULL || ($cost !== NULL && $total < $cost)) {
              $cost = $total;
              $code = $service_option->serviceLevelCode;
            }
          }
        }

        // if we found shipping rates, then use it for these items.
        if ($code !== NULL) {
          $shipping_code = $code;
        }
      }
    }

    return array(
      'items' => $line_items,
      'shipping_code' => $shipping_code,
    );
  };

  $decorated_order['line_item_bundles'] = array_map($add_shipping_codes, $decorated_order['line_item_bundles']);

  return $decorated_order;
}

/**
 * Get and add the shipping code to a decorated orded.
 */
function lulzbot_store_add_line_items_warehouses($decorated_order) {
  $shipwire_warehouses = shipwire_api_warehouses();

  foreach ($decorated_order['line_item_bundles'] as $category => &$bundle) {
    switch ($category) {
    case 'printers':
      $bundle['warehouse'] = $shipwire_warehouses['Chicago'];
      break;
    case 'no-printers':
      $bundle['warehouse'] = $shipwire_warehouses['Philadelphia'];
      break;
    default:
      $bundle['warehouse'] = $decorated_order['warehouses'][0];
    }
  }

  return $decorated_order;
}

/**
 * Place shipwire orders for the given commerce order.
 *
 * This takes a commerce order, processes it and places any necessary shipwire
 * orders.
 *
 * @param stdClass $commerce_order
 *  A commerce order
 */
function lulzbot_store_place_shipwire_order($commerce_order) {
  // Get decorated order from commerce order.
  $decorated_order = lulzbot_store_get_decorated_order($commerce_order);

  // Build out individual shipwire orders for each bundle.
  $decorated_order = lulzbot_store_add_order_shipwire_orders($decorated_order);

  // This needs to be uncommented when you are ready to test against the dev
  // shipwire api.
  $shipwire_orders = lulzbot_store_post_shipwire_orders($decorated_order);
}

/**
 * Get a decorated order array.
 *
 * This takes a commerce_order and returns an array with appropriate warehouses,
 * split bundles (printers/non-printers), appropriate shipping codes, etc.
 *
 * @param stdClass $commerce_order
 *  A commerce order
 */
function lulzbot_store_get_decorated_order($commerce_order) {
  // Create an initial decorated array.
  $decorated_order = array('commerce_order' => $commerce_order);

  // Decorate the order with line items.
  $decorated_order = lulzbot_store_add_order_line_items($decorated_order);
  // Add the warehouses that this order should be fulfilled by.
  $decorated_order = lulzbot_store_add_order_warehouses($decorated_order);
  // If the order should be fulfilled by separate warehouses, bundle the line
  // items up accordingly.
  $decorated_order = lulzbot_store_split_order_line_items($decorated_order);

  // Add the appropriate shipping level code to each line item bundle.
  $decorated_order = lulzbot_store_add_line_items_ship_codes($decorated_order);
  // Add the appropriate warehouse to each line item bundle.
  $decorated_order = lulzbot_store_add_line_items_warehouses($decorated_order);

  return $decorated_order;
}

/**
 * Extract line items from commerce order and add to decorated orded.
 */
function lulzbot_store_add_order_line_items($decorated_order) {
  $commerce_order = $decorated_order['commerce_order'];

  $line_items = lulzbot_store_get_order_line_items($commerce_order);

  $decorated_order['line_items'] = $line_items;

  return $decorated_order;
}

/**
 * Get and add the shipping code to a decorated orded.
 */
function lulzbot_store_add_order_warehouses($decorated_order) {
  $countries_config = lulzbot_store_get_countries_config();
  $order_country = lulzbot_store_get_order_country($decorated_order['commerce_order']);
  $country_config = $countries_config[$order_country];
  $decorated_order['warehouses'] = explode(',', $country_config->warehouses);
  return $decorated_order;
}

/**
 * Split printer and other line items apart if shipping from the US.
 */
function lulzbot_store_split_order_line_items($decorated_order) {
  if (_lulzbot_store_order_is_mixable($decorated_order)) {
    $sort_line_items = function ($carry, $line_item) {
      $product = stools_field_value($line_item, 'commerce_product', LANGUAGE_NONE, array('key' => 'product_id'));
      $product = commerce_product_load($product);
      $category = ($product->type === 'printer') ? 'printers' : 'no-printers';
      $carry[$category][] = $line_item;
      return $carry;
    };

    $sorted_line_items = array_reduce(
      $decorated_order['line_items'],
      $sort_line_items,
      array()
    );
  }
  else {
    $sorted_line_items = array('all' => $decorated_order['line_items']);
  }

  $decorated_order['line_item_bundles'] = $sorted_line_items;

  return $decorated_order;
}

/**
 * Get the Shipwire order array.
 */
function lulzbot_store_add_order_shipwire_orders($decorated_order) {
  foreach ($decorated_order['line_item_bundles'] as $category => $bundle) {
    $shipwire_orders[] = _lulzbot_store_build_shipwire_order(
      $decorated_order['commerce_order'],
      $bundle['items'],
      $bundle['warehouse'],
      $bundle['shipping_code'],
      $category
    );
  }

  $decorated_order['shipwire_orders'] = $shipwire_orders;
  return $decorated_order;
}

/**
 * Send the shipwire order(s).
 */
function lulzbot_store_post_shipwire_orders($decorated_order) {
  $api = shipwire_api_request();
  $commerce_order = $decorated_order['commerce_order'];

  // flag this as debuggable if the option is set.
  if (variable_get('lulzbot_store_debug_shipwire_orders', FALSE)) {
    $api->debug();
  }

  // loop through the order(s)
  $order_count = 0;
  foreach ($decorated_order['shipwire_orders'] as $shipwire_order) {
    $response = $api->post()->orders($shipwire_order);
    if ($response->isError()) {
      drupal_set_message(t('There was an error creating this order.'), 'error');
      watchdog(
        'lulzbot_store',
        'Error creating Shipwire order',
        array(),
        WATCHDOG_ERROR,
        l(t('Order'), 'admin/commerce/orders/' . $commerce_order->order_number)
      );
      continue;
    }

    // save order info into our order-shipwire-order table
    foreach ($response->resource->items as $shipwire_order_info) {
      lulzbot_store_save_shipwire_order($commerce_order, $shipwire_order_info);
      $order_count++;
    }
  }
  watchdog(
    'lulzbot_store',
    'Shipwire !orders created for order !num using ' . __FUNCTION__,
    array(
      '!orders' => format_plural($order_count, 'order', 'orders'),
      '!num' => $commerce_order->order_number,
    ),
    WATCHDOG_INFO
  );
}

/**
 * Get the Shipwire order array.
 */
function lulzbot_store_get_shipwire_order($order, $line_items, $warehouse, $shipping_code, $id_suffix = NULL) {
  $shipwire_order = _lulzbot_store_build_shipwire_order($order, $line_items, $warehouse, $shipping_code, $id_suffix);
  return $shipwire_order;
}

/**
 * Determine if this order should be a mixed order to shipwire.
 *
 * Currently, this means any order which is being fulfilled from more than one
 * warehouse.
 *
 * @todo: make this configuration more explicit.
 */
function _lulzbot_store_order_is_mixable($decorated_order) {
  return (count($decorated_order['warehouses']) > 1);
}

/**
 * Get the Shipwire order array.
 */
function _lulzbot_store_build_shipwire_order($order, $line_items, $warehouse, $shipping_code, $id_suffix = NULL) {
  $order_number = (isset($id_suffix)) ? "{$order->order_number}-{$id_suffix}" : string($order->order_number);
  $shipwire = array(
    'orderNo' => $order_number,
    'items' => array_map('shipwire_api_map_line_items', $line_items),
    'options' => array(
      'canSplit' => variable_get('lulzbot_store_can_split_orders', 1),
      'hold' => 1,
      'holdReason' => 'Initial order hold for processing',
      'serviceLevelCode' => $shipping_code,
      'forceDuplicate' => variable_get('lulzbot_store_force_duplicate_orders', TRUE),
    ),
    'shipFrom' => array('company' => 'LulzBot'),
    'shipTo' => shipwire_api_get_order_shipping_address($order),
  );
  if (!is_numeric($warehouse)) {
    $shipwire['options']['warehouseRegion'] = $warehouse;
  }
  elseif (is_numeric($warehouse)) {
    $shipwire['options']['warehouseId'] = $warehouse;
  }

  $shipping_profile = stools_field_value($order, 'commerce_customer_shipping', LANGUAGE_NONE, array('key' => 'profile_id'));
  $shipping = commerce_customer_profile_load($shipping_profile);
  $shipwire['shipTo']['phone'] = stools_field_value($shipping, 'field_customer_phone');
  return $shipwire;
}

/**
 * Save a shipwire order details.
 */
function lulzbot_store_save_shipwire_order($order, $shipwire_order_info) {
  $shipwire_order_details = array('commerce_order_id' => $order->order_number);
  $shipwire_order_details['shipwire_order_id'] = $shipwire_order_info->resource->id;
  $shipwire_order_details['status'] = $shipwire_order_info->resource->status;
  $shipwire_order_details['on_hold'] = $shipwire_order_info->resource->status === 'held' ? 1 : 0;
  $shipwire_order_details['shipped'] = 0;

  db_merge('lulzbot_store_shipwire_orders')
    ->key(array('commerce_order_id' => $order->order_number, 'shipwire_order_id' => $shipwire_order_info->resource->id))
    ->fields($shipwire_order_details)
    ->execute();
}

/**
 * Get shipwire orders from our internal list of orders.
 */
function lulzbot_store_get_shipwire_order_data(array $options = array()) {
  $query = db_select('lulzbot_store_shipwire_orders', 's');
  $query->fields('s');

  if (isset($options['shipped'])) {
    $query->condition('s.shipped', $options['shipped'], '=');
  }

  if (isset($options['delivered'])) {
    $query->condition('s.delivered', $options['delivered'], '=');
  }

  if (isset($options['order'])) {
    $query->condition('s.commerce_order_id', intval($options['order']), '=');
  }

  if (isset($options['limit'])) {
    $query->range(0, $options['limit']);
  }

  $results = $query->execute();
  return $results->fetchAllAssoc('shipwire_order_id');
}

/**
 * Try to release the order.
 *
 * @param object $order
 *   The commerce order.
 * @param object $shipwire_order
 *   The shipwire order record from the DB.
 *
 * @return bool
 *   Returns TRUE if the holds were released, FALSE if not.
 */
function lulzbot_store_shipwire_order_release_hold($order, $shipwire_order) {
  $api = shipwire_api_request();

  // tell the DB we're processing this release
  db_update('lulzbot_store_shipwire_orders')
    ->fields(array('processing_release' => 1))
    ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id)
    ->execute();

  // get holds for this order
  $response = $api->orders($shipwire_order->shipwire_order_id, 'holds');
  if ($response->isError()) {
    watchdog(
      'lulzbot_store',
      'There was an error clearing the holds on order :order (Shipwire order :shipwire) while checking holds for the order: :response',
      array(
        ':order' => $order->order_number,
        ':response' => json_encode($response->data),
        ':shipwire' => $shipwire_order->shipwire_order_id,
      ),
      WATCHDOG_ERROR
    );

    // release the processing flag for this shipwire order so we can try again
    // later
    db_update('lulzbot_store_shipwire_orders')
      ->fields(array('processing_release' => 0))
      ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id)
      ->execute();
    return FALSE;
  }

  // check if the order is processing
  $processing = FALSE;
  foreach ($response->resource->items as $item) {
    if ($item->resource->description === 'Order is currently being posted') {
      $processing = TRUE;
      break;
    }
  }

  if ($processing) {
    watchdog(
      'lulzbot_store',
      'The Shipwire order holds were not cleared for :order: the order is still processing on Shipwire: :shipwire :response',
      array(
        ':order' => $order->order_number,
        ':response' => json_encode($response->data),
        ':shipwire' => $shipwire_order->shipwire_order_id,
      ),
      WATCHDOG_NOTICE
    );

    // release the processing flag for this shipwire order so we can try again
    // later.
    db_update('lulzbot_store_shipwire_orders')
      ->fields(array('processing_release' => 0))
      ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id)
      ->execute();
    return FALSE;
  }

  // update this order
  $response = $api->post()->orders($shipwire_order->shipwire_order_id, 'holds', 'clear');
  if (!$response->isError()) {
    db_update('lulzbot_store_shipwire_orders')
      ->fields(array('on_hold' => 0, 'release_hold' => 0, 'processing_release' => 0))
      ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id, '=')
      ->execute();

    watchdog(
      'lulzbot_store',
      'Shipwire holds lifted on order :order, response: :response',
      array(
        ':order' => $order->order_number,
        ':response' => json_encode($response->data),
      ), WATCHDOG_NOTICE);
    return TRUE;
  }

  watchdog(
    'lulzbot_store',
    'There was an error clearing the holds on order :order (shipwire order :shipwire): :response',
    array(
      ':order' => $order->order_number,
      ':response' => json_encode($response->data),
      ':shipwire' => $shipwire_order->shipwire_order_id,
    ),
    WATCHDOG_ERROR
  );

  // release the processing flag for this shipwire order so we can try again
  // later
  db_update('lulzbot_store_shipwire_orders')
    ->fields(array('processing_release' => 0))
    ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id)
    ->execute();
  return FALSE;
}

/**
 * Find related products.
 */
function lulzbot_store_find_related_products($product) {
  static $related = array();

  if (!isset($related[$product->product_id])) {
    // find the display nodes that use this product
    $query = db_select('field_data_field_product_reference', 'r');
    $query->fields('r')
      ->condition('field_product_reference_product_id', $product->product_id, '=');
    $display_nodes = $query->execute()->fetchAll();
    $display_node_ids = array_map('lulzbot_store_map_node_ids', $display_nodes);
    $related_query = db_select('field_data_field_product_reference', 'r')
      ->fields('r', array('field_product_reference_product_id'));
    $related_query->condition('entity_id', $display_node_ids, 'IN');
    $related_query->join('commerce_product', 'p', 'r.field_product_reference_product_id=p.product_id');
    $related_query->fields('p', array('sku'));
    $related_products = $related_query->execute()->fetchAll();
    $related[$product->product_id] = array_map('lulzbot_store_map_product_ids', $related_products);
  }

  return $related[$product->product_id];
}

/**
 * Return the node IDs for the display nodes.
 *
 * @see lulzbot_store_find_related_products()
 */
function lulzbot_store_map_node_ids($item) {
  return $item->entity_id;
}

/**
 * Return the related products IDs for the display nodes.
 *
 * @see lulzbot_store_find_related_products()
 */
function lulzbot_store_map_product_ids($item) {
  return array('id' => $item->field_product_reference_product_id, 'sku' => $item->sku);
}

/**
 * Signifyd webhook callback.
 *
 * Receives post requests from the web service when a case has been resolved.
 * The request has a header we need to verify.
 */
function lulzbot_store_webhook_signifyd() {
  $debug = variable_get('lulzbot_store_debug_signifyd_webhook', FALSE);
  // if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
  //   if ($debug) {
  //     watchdog('lulzbot_store', 'Request with invalid method to the signifyd webhook: :method :request', array(':method' => $_SERVER['REQUEST_METHOD'], ':request' => json_encode($_SERVER)), WATCHDOG_ERROR);
  //   }
  //   drupal_add_http_header('Status', '403 Access Denied');
  //   drupal_json_output(array());
  //   return drupal_exit();
  // }

  // verify the header
  if (!isset($_SERVER['HTTP_X_SIGNIFYD_SEC_HMAC_SHA256'])) {
    if ($debug) {
      watchdog('lulzbot_store', 'Hash not present: :keys', array(':keys' => implode(', ', array_keys($_SERVER))), WATCHDOG_ERROR);
    }
    drupal_add_http_header('Status', '403 Access Denied');
    drupal_json_output(array());
    return drupal_exit();
  }

  // get the header
  $header = $_SERVER['HTTP_X_SIGNIFYD_SEC_HMAC_SHA256'];

  // get the API key
  $api_key = variable_get('signifyd_api_key', 'abcde');

  // get the JSON body
  $body = file_get_contents('php://input');

  // calculate the hash
  $hash = base64_encode(hash_hmac('sha256', $body, $api_key, TRUE));

  // copied from old webhooks script.
  $res = $hash ^ $header;
  $ret = strlen($hash) ^ strlen($header);
  for ($i = strlen($res) - 1; $i >= 0; $i--) {
    $ret += ord($res[$i]);
  }
  if ($ret !== 0) {
    // the hashes don't match
    if ($debug) {
      watchdog('lulzbot_store', 'Hashes do not match: ' . $hash, array(), WATCHDOG_ERROR);
    }
    drupal_add_http_header('Status', '403 Access Denied');
    drupal_json_output(array());
    return drupal_exit();
  }

  // decode the message
  $data = $body;
  $body = json_decode($body);

  // update the order status
  $order = commerce_order_load($body->orderId);
  if (!$order) {
    if ($debug) {
      watchdog('lulzbot_store', 'Request with invalid order to the signifyd webhook: :order', array(':order' => $body->orderId), WATCHDOG_ERROR);
    }
    drupal_add_http_header('Status', '404 Page Not Found');
    drupal_json_output(array());
    return drupal_exit();
  }

  // figure out the status we should set the order to
  $status = variable_get('lulzbot_store_post_signifyd_status', 'processing_payment');

  // for WPS payments, skip payment because it is captured at time of order
  $is_wps_payment = $order->data['payment_method'] === 'paypal_wps|commerce_payment_paypal_wps';
  if ($is_wps_payment) {
    $status = 'processing_shipping';
  }

  $message = 'Signifyd verification passed';
  if (strtolower($body->guaranteeDisposition) !== 'approved') {
    $message = 'Signifyd verification failed';
    if (!$is_wps_payment) {
      //$status = 'canceled';
      $status = 'hold_for_review';
    }
    else {
      $status = 'hold_for_review';
    }
  }

  // save the signifyd response to the database.
  db_merge('lulzbot_store_signifyd')
    ->key(array('order_id' => $order->order_number))
    ->fields(array('response' => $data, 'updated' => time()))
    ->execute();

  commerce_order_status_update($order, $status, FALSE, TRUE, $message);
  watchdog('lulzbot_store', 'Signifyd status updated for order :order via webhook to !status', array(':order' => $order->order_number, '!status' => $status), WATCHDOG_NOTICE, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
  drupal_json_output(array());
  drupal_exit();
}

/**
 * Update order status with Shipwire.
 */
function lulzbot_store_orders_update_batch($batch_size = 10) {
  $options = array(
    'delivered' => 0,
  );
  $orders = lulzbot_store_get_shipwire_order_data($options);

  $batch = array(
    'title' => t('Updating orders'),
    'operations' => array(),
    'file' => drupal_get_path('module', 'lulzbot_store') . '/lulzbot_store.inc',
    'finished' => 'lulzbot_store_orders_update_finished',
  );

  $order_sets = array_chunk(array_keys($orders), $batch_size);

  foreach ($order_sets as $order_set) {
    //lulzbot_store_orders_update_process($order_set, $orders, $batch);
    $batch['operations'][] = array(
      'lulzbot_store_orders_update_process',
      array($order_set, $orders),
    );
  }

  return $batch;
}

/**
 * Update order status with Shipwire.
 *
 * Only updates shipwire orders that have not been marked delivered in our DB.
 */
function lulzbot_store_orders_update_process($order_ids, $orders, &$context) {
  $order_controller = entity_get_controller('commerce_order');

  // get a list of order IDs that have not shipped yet.
  //$order_ids = array_keys($orders);
  $order_ids_list = implode(',', $order_ids);

  // ask shipwire for order details. results are paginated, so we need to loop
  // through and keep getting results as long as we have them.
  $api = shipwire_api_request();
  $response = $api->orders(array(
    'orderId' => $order_ids_list,
  ));

  $updates = array(
    'status' => array(),
    'on_hold' => array(),
    'shipped' => array(),
    'delivered' => array(),
  );

  do {
    $count = 0;
    foreach ($response->resource->items as $item) {
      // figure out if this order has shipped.
      $held = intval($item->resource->status === 'held');
      $shipped = intval(in_array($item->resource->status, array('completed', 'delivered')));
      $delivered = intval($item->resource->status === 'delivered');

      $updates['status'][$item->resource->status][] = $item->resource->id;
      $updates['on_hold'][$held][] = $item->resource->id;
      $updates['shipped'][$shipped][] = $item->resource->id;
      $updates['delivered'][$delivered][] = $item->resource->id;

      $count++;
    }
  } while ($response = $api->next());

  $order_update = function ($column, $value, $ids) {
    db_update('lulzbot_store_shipwire_orders')
      ->fields(array(
        $column => $value,
      ))
      ->condition('shipwire_order_id', $ids, 'IN')
      ->execute();
  };

  array_walk($updates, function ($vals, $col) use ($order_update) {
    array_walk($vals, function ($ids, $val) use ($order_update, $col) {
      $order_update($col, $val, $ids);
    });
  });

  // fire off an event trigger
  rules_invoke_event('lulzbot_store_shipwire_orders_updated');
}

/**
 * Update orders which have had all shipments delivered.
 */
function lulzbot_store_orders_update_finished() {
  // Get all commerce_orders that are not 'completed' and whose total delivered
  // items are equal to the number of shipwire shipments.
  $result = db_query("SELECT order_id
    FROM {commerce_order} AS orders
    JOIN lulzbot_store_shipwire_orders as shipments 
    ON orders.order_id = shipments.commerce_order_id
    AND orders.status != 'completed'
    GROUP BY orders.order_id
    HAVING SUM(shipments.shipped) = COUNT(shipments.shipwire_order_id)"
    );

  //if (isset($commerce_orders) && is_array($commerce_orders)) {
  while ($order = $result->fetchObject()) {
    $commerce_order = commerce_order_load($order->order_id);
    commerce_order_status_update($commerce_order, 'completed', FALSE, TRUE, 'Shipwire has fulfilled the order.');
  }
}
