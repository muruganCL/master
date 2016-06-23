<?php

if (php_sapi_name() !== 'cli') {
  exit;
}

// create an order
$order = commerce_order_new(1, 'pending_verification');
commerce_order_save($order);

// product line item
$product = commerce_product_load_by_sku('tshirt-black-us');
$line_item = commerce_product_line_item_new($product, 1, $order->order_id);
commerce_line_item_save($line_item);

// printer line item
$printer = commerce_product_load_by_sku('817752014328');
$line_item2 = commerce_product_line_item_new($printer, 1, $order->order_id);
commerce_line_item_save($line_item2);

// shipping line item
$shipping = commerce_line_item_new('shipping', $order->order_id);
$shipping_wrapper = entity_metadata_wrapper('commerce_line_item', $shipping);
$shipping_wrapper->commerce_shipping_service = 'lulzbot_store_free_shipping';
commerce_line_item_save($shipping);

$order_wrapper = entity_metadata_wrapper('commerce_order', $order);
$order_wrapper->commerce_line_items[] = $line_item;
$order_wrapper->commerce_line_items[] = $line_item2;
$order_wrapper->commerce_line_items[] = $shipping;
commerce_order_save($order);
print "Order Number: " . $order->order_number . "\n";

module_load_include('inc', 'lulzbot_store');
module_load_include('inc', 'lulzbot_store', 'lulzbot_store.rules');

$warehouses = lulzbot_store_get_shipwire_warehouses_for_order($order);
print "Warhouses: " . implode(', ', $warehouses) . "\n";

// get the product line items for this order
$line_items = lulzbot_store_get_order_line_items($order);
$shipping_code = $printer_shipping_code = $other_shipping_code = shipwire_api_get_shipping_code_from_order($order);

// figure out if the order contains a printer and divide the line items up
// into containers for printers & non-printers.
$has_printer = FALSE;
$has_other_items = FALSE;
$printer_line_items = array();
$non_printer_line_items = array();
foreach ($line_items as $line_item) {
  $product = stools_field_value($line_item, 'commerce_product', LANGUAGE_NONE, array('key' => 'product_id'));
  $product = commerce_product_load($product);
  if ($product->type === 'printer') {
    $has_printer = TRUE;
    $printer_line_items[] = $line_item;
  }
  else {
    $has_other_items = TRUE;
    $non_printer_line_items[] = $line_item;
  }
}

$profile = stools_field_value($order, 'commerce_customer_shipping', LANGUAGE_NONE, array('key' => 'profile_id'));
$profile = commerce_customer_profile_load($profile);
$rates = shipwire_api_get_default_rates_for_order($order, $profile, $printer_line_items);

$api = shipwire_api_request();
$response = $api->post()->rate($rates[0]);
if ($response->isError()) {
  print "Error\n";
  exit(1);
}

// find the cheapest rate.
if (isset($response->resource->rates)) {
  $cost = NULL;
  $code = NULL;
  foreach ($response->resource->rates as $rate) {
    foreach ($rate->serviceOptions as $serviceOption) {
      foreach ($serviceOption->shipments as $shipment) {
        var_dump($shipment);
      }
    }
  }
}
else {
  var_dump($response);
  exit(1);
}

// lulzbot_store_action_place_us_shipwire_orders($order);

// $orders = db_select('lulzbot_store_shipwire_orders', 'o')
//   ->fields('o')
//   ->condition('commerce_order_id', $order->order_number, '=')
//   ->execute()
//   ->fetchAllAssoc('shipwire_order_id');
// // var_dump($orders);
