<?php

/**
 * Callback function for our tracking_numbers field.
 */
function lulzbot_store_ui_extra_field_tracking_numbers_callback($entity) {
  // Wrap the commerce_order.
  $order = entity_metadata_wrapper('commerce_order', $entity);

  // Get an array of shipwire shipment ids.
  $shipment_ids = _lulzbot_store_ui_get_shipment_ids($order->getIdentifier());

  // Load a shipwire_api client.
  $shipwire_client = _lulzbot_store_ui_get_shipwire_client();
  
  // Get an array of all shipwire trackings from the shipwire API.
  $trackings = array_map(function ($shipment_id) use ($shipwire_client) {
    return _lulzbot_store_ui_get_shipwire_shipment_trackings($shipwire_client, $shipment_id);
  }, $shipment_ids);

  // Extract a single array of tracking links from all of the shipments.
  $tracking_links = array_reduce($trackings, function ($links, $tracking) {
    return array_merge($links, _lulzbot_store_ui_get_tracking_links($tracking));
  }, array());

  // Create a list of links and return that as markup for the field.
  return array(
    '#markup' => (empty($tracking_links)) ? 'Pending' : implode(', ', $tracking_links),
  );
}

/**
 * Helper function to look up all shipwire shipment ids by order id.
 */
function _lulzbot_store_ui_get_shipment_ids($order_id) {
  $shipment_id_query = function ($order_id) {
    $query = db_select('lulzbot_store_shipwire_orders', 'l');
    $query->condition('l.commerce_order_id', $order_id, '=');
    $query->fields('l', array('shipwire_order_id'));
    $result = $query->execute()->fetchAllAssoc('shipwire_order_id');

    return array_keys($result);
  };

  return $shipment_id_query($order_id);

  //return _lulzbot_store_ui_cache_helper(
  //  __FUNCTION__,
  //  $shipment_id_query,
  //  array($order_id)
  //);
}

/**
 * Helper function to get tracking links given a shipwire tracking object.
 */
function _lulzbot_store_ui_get_tracking_links($tracking) {
  if (!isset($tracking->data->resource->items)) return FALSE;

  $create_link = function ($tracking_item) {
    $resource = $tracking_item->resource;
    return l($resource->tracking, $resource->url);
  };

  $tracking_items = $tracking->data->resource->items;

  return array_map($create_link, $tracking_items);
}

/**
 * Helper function to get and cache a shipwire shipment api request.
 */
function _lulzbot_store_ui_get_shipwire_shipment_trackings($shipwire_client, $shipment_id) {
  $request = function ($shipwire_client, $shipment_id) {
    $trackings =  $shipwire_client->orders($shipment_id, "trackings");
    return $trackings;
  };

  return $request($shipwire_client, $shipment_id);

  //return _lulzbot_store_ui_cache_helper(
  //  __FUNCTION__,
  //  $request,
  //  array($shipment_id),
  //  TRUE
  //);
}

/**
 * Helper function to load a shipwire_api client.
 */
function _lulzbot_store_ui_get_shipwire_client() {
  module_load_include('inc', 'shipwire_api');
  return new ShipwireAPI();
}

/**
 * Helper for caching things.
 */
function _lulzbot_store_ui_cache_helper($cache_key, $func, array $args, $reset = FALSE) {
  $key = md5($cache_key . serialize($args));
  $data = &drupal_static($key, NULL, $reset);
  if (!$data || $reset) {
    if ($db_cache = cache_get("lulzbot_store_ui|$cache_key")) {
      $db_cache_array = $db_cache->data;
      if (!$reset && isset($db_cache_array[$key])) {
        $data = $db_cache_array[$key];
      }
      else {
        $data = call_user_func_array($func, $args);
        $db_cache_array[$key] = $data;
        cache_set("lulzbot_store_ui|$cache_key", $db_cache_array, 'cache');
      }
    }
    else {
      $data = call_user_func_array($func, $args);
      $db_cache_array = array($key => $data);
      cache_set("lulzbot_store_ui|$cache_key", $db_cache_array, 'cache');
    }
  }
  return $data;
}
