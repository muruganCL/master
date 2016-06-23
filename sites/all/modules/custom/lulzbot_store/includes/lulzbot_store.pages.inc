<?php
/**
 * Menu callback for store page.
 */
function lulzbot_store_create_store_page() {
  drupal_add_js(drupal_get_path('theme', 'lulzbot') . '/build/js/store.js');
  return '';
}

/**
 * Menu callback for filament page.
 */
function lulzbot_store_create_filament_page() {
  return '';
}

/**
 * Menu callback for filament page.
 */
function lulzbot_store_create_merchandise_page() {
  return '';
}

/**
 * Menu callback for parts page.
 */
function lulzbot_store_create_parts_page() {
  return '';
}

/**
 * Menu callback for toolheads page.
 */
function lulzbot_store_create_toolheads_page() {
  return '';
}

/**
 * Redirect to the filament color image.
 *
 * Finds filaments associated with the current node, returning the first image
 * for the requested color. It then redirects to that image.
 */
function lulzbot_store_filament_color_image($product_id, $color) {
  $cid = 'lulzbot_store_color_image_' . $product_id . '_' . $color;
  $color_image = cache_get($cid);
  if ($color_image && stools_use_cache($color_image)) {
    header('Location: ' . image_style_url('filament_color', $color_image->data));
    exit;
  }

  // find filament products with the color
  $exists = db_query('SELECT nid FROM node WHERE nid=:nid', array(':nid' => $product_id))->fetchColumn();
  if (!$exists) {
    return drupal_not_found();
  }

  $results = db_query('SELECT field_product_reference_product_id FROM field_data_field_product_reference WHERE entity_id=:nid', array(':nid' => $product_id))->fetchAll();
  $product_ids = array();
  foreach ($results as $result) {
    $product_ids[] = intval($result->field_product_reference_product_id);
  }
  $filament_colors = db_query('SELECT * FROM commerce_product p
    JOIN field_data_field_product_filament_colors c
    ON c.entity_id=p.product_id AND c.revision_id=p.revision_id
    WHERE p.product_id IN (:ids) AND c.field_product_filament_colors_tid = :color', array(':ids' => $product_ids, ':color' => $color));
  while ($this_color = $filament_colors->fetchAssoc()) {
    $product = commerce_product_load($this_color['product_id']);
    if (stools_field_has_value($product, 'field_product_filament_image')) {
      $image = stools_field_value($product, 'field_product_filament_image');
      cache_set($cid, $image['uri'], 'cache', strtotime('+1 hour'));
      header('Location: ' . image_style_url('filament_color', $image['uri']));
      exit;
    }
  }

  return drupal_not_found();
}

/**
 * Preprocess the order page.
 *
 * Called from the theme.
 */
function lulzbot_store_order_page_alter(&$page) {
  $args = arg();
  $order_number = $args[3];
  if (isset($page['content']['system_main']['commerce_order'])) {
    $order =& $page['content']['system_main']['commerce_order'][$order_number];
    $status = commerce_order_status_load($order['#entity']->status);

    $page['content']['system_main']['commerce_order'][$order_number]['order_status'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="order-status"><strong>Order status:</strong> ' . $status['title'] . '</div>',
      '#weight' => -100,
    );

    module_load_include('inc', 'lulzbot_store');
    $shipments = lulzbot_store_get_shipwire_order_data(array('order' => $order['#entity']->order_number));
    if ($shipments) {
      $page['content']['system_main']['commerce_order'][$order_number]['shipments'] = array(
        '#type' => 'markup',
        '#prefix' => '<div class="shipments"><h2>Shipments</h2>',
        '#suffix' => '</div>',
        '#weight' => 100,
      );

      $shipment_ids = array_keys($shipments);
      $response = shipwire_api_request()
        ->cacheable('+10 minutes')
        ->orders(array('orderId' => implode(',', $shipment_ids), 'expand' => 'holds,trackings'));

      if ($response->isError()) {
        $page['content']['system_main']['commerce_order'][$order_number]['shipments']['error'] = array(
          '#type' => 'markup',
          '#markup' => '<div class="message error"><p>There was an error retrieving shipping information. Please try again later.</p></div>',
        );
        return;
      }

      $administer = user_access('administer commerce_order entities');

      if ($administer) {
        drupal_set_message(t('View admin page for this order: !order', array('!order' => l(t('Order'), 'admin/commerce/orders/' . $order['#entity']->order_number))), 'status');
      }

      $headers = array('Shipment', 'Status', 'Type', 'Tracking');
      $rows = array();
      $methods = commerce_shipping_services();
      foreach ($response->resource->items as $item) {
        $tracking_response = shipwire_api_request()->orders($item->resource->id, 'trackings');
        $status = $item->resource->status === 'held' ? 'on hold' : $item->resource->status;

        // if this is held, try to provide a reason to the customer.
        if ($item->resource->status === 'held' && isset($item->resource->holds)) {
          $holds = array();
          $out_of_stock = FALSE;
          foreach ($item->resource->holds->resource->items as $hold_item) {
            $holds[] = $hold_item->resource;
            if ($hold_item->resource->description === 'Insufficient stock') {
              $out_of_stock = TRUE;
            }
          }

          if ($out_of_stock) {
            $status .= ', restocking';
          }
        }

        // add tracking information if it is available.
        $tracking = '&mdash;';
        if ($item->resource->trackings->resource->total > 0) {
          $trackings = array();
          foreach ($item->resource->trackings->resource->items as $tracking_item) {
            $trackings[] = l($tracking_item->resource->summary, $tracking_item->resource->url);
          }
          if ($trackings) {
            $tracking = implode(', ', $trackings);
          }
        }

        $service_code = $item->resource->options->resource->serviceLevelCode;
        $service_code = str_replace('-', '_', strtolower($service_code));
        $service_code = 'shipwire_api_' . $service_code;

        if (isset($methods[$service_code])) {
          $service = $methods[$service_code]['title'];
        }
        else {
          $service = t('Other');
        }

        $rows[] = array($item->resource->id, $status, $service, $tracking);
      }

      $page['content']['system_main']['commerce_order'][$order_number]['shipments-head'] = array(
        '#markup' => '<h4>' . t('Shipping Information') . '</h4>',
        '#weight' => -21,
      );

      $page['content']['system_main']['commerce_order'][$order_number]['shipments'] = array(
        '#type' => 'table',
        '#header' => $headers,
        '#rows' => $rows,
        '#empty' => '<p>No shipments have been created yet.</p>',
        '#weight' => -20,
      );

      $page['content']['system_main']['commerce_order'][$order_number]['details-head'] = array(
        '#markup' => '<h4>' . t('Order Details') . '</h4>',
        '#weight' => -19,
      );

      //drupal_set_breadcrumb(array(
      //  l("My Account", sprintf("user/%s/orders", $order['#entity']->uid)),
      //  t('Order Details'),
      //));
    }
  }
}
