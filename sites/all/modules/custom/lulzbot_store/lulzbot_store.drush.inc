<?php

/**
 * Implements hook_drush_command().
 */
function lulzbot_store_drush_command() {
  return array(
    'product-availability' => array(
      'description' => dt('Update product availability and send notices.'),
    ),
    'order-status' => array(
      'description' => dt('Get the order status'),
      'arguments' => array(
        'order' => 'The order ID',
      ),
    ),
    'order-verification' => array(
      'description' => dt('Update order verification manually'),
      'arguments' => array(
        'order' => 'The order ID',
        'status' => 'Either ok/fail',
      ),
    ),
    'orders-update' => array(
      'description' => dt('Check/update the status of orders with Shipwire.'),
    ),

    'release-holds' => array(
      'description' => dt('Release shipping holds if needed.'),
    ),

    'cleanup-data' => array(
      'description' => dt('Cleanup lulzbot_store_data table'),
    ),
  );
}

/**
 * Update product availability and check if there are notifications to send.
 */
function drush_lulzbot_store_product_availability() {
  module_load_include('inc', 'lulzbot_store', 'lulzbot_store.availability');

  // get any unsent notifications
  $notifications = array();
  $products = db_query('SELECT DISTINCT sku FROM lulzbot_store_notify WHERE sent=0')->fetchAllAssoc('sku');
  foreach ($products as $product) {
    $availability = lulzbot_store_product_availability($product->sku, array('cache' => FALSE));

    if (!empty($availability)) {
      // get a list of emails that need this notification
      $emails = db_query('SELECT mail, country FROM lulzbot_store_notify WHERE sent=0 AND sku=:sku', array(':sku' => $product->sku));
      while ($email = $emails->fetchAssoc()) {
        // add this email if the thing is available for the requested country
        if (lulzbot_store_product_is_available($product->sku, $email['country'])) {
          if (!isset($notifications[$email['mail']])) {
            $notifications[$email['mail']] = array();
          }
          $notifications[$email['mail']][] = $product->sku;
        }
      }
    }
  }

  $operations = array();
  foreach ($notifications as $email => $skus) {
    $operations[] = array('lulzbot_store_send_notification', array($email, $skus));
  }

  $batch = array(
    'title' => 'Notifications',
    'operations' => $operations,
    'finished' => 'lulzbot_store_notifications_finished',
    'file' => drupal_get_path('module', 'lulzbot_store') . '/lulzbot_store.availability.inc',
  );
  batch_set($batch);
  $batch =& batch_get();
  $batch['progressive'] = FALSE;
  drush_backend_batch_process();
}

/**
 * Set the verification status for an order manually.
 */
function drush_lulzbot_store_order_verification($order, $status) {
  if (!is_numeric($order) || !in_array($status, array('ok', 'fail'))) {
    drush_log(t('Usage: drush order-verification [order id] [ok|fail]'), 'error');
    return;
  }

  // load the order
  $commerce_order = commerce_order_load($order);
  if (!$commerce_order) {
    drush_log(t('Could not find requested order'), 'error');
    return;
  }

  // we only want to act on orders that are pending verification.
  if ($commerce_order->status === 'pending_verification') {
    $status = $status ? variable_get('lulzbot_store_post_signifyd_status', 'processing_payment') : 'canceled';
    commerce_order_status_update($commerce_order, $status);
    drush_log(t('Order status updated to: !status', array('!status' => $status)), 'ok');
  }
}

/**
 * Get the status for an order.
 */
function drush_lulzbot_store_order_status($order) {
  if (!is_numeric($order)) {
    drush_log(t('Usage: drush order-status [order id]'), 'error');
    return;
  }

  // load the order
  $commerce_order = commerce_order_load($order);
  if (!$commerce_order) {
    drush_log(t('Could not find requested order'), 'error');
    return;
  }
  drush_log(t('Order status: !status', array('!status' => $commerce_order->status)), 'ok');
}

/**
 * Update order status with Shipwire.
 */
function drush_lulzbot_store_orders_update($batch_size = 10) {
  module_load_include('inc', 'lulzbot_store');
  $batch = lulzbot_store_orders_update_batch();
  batch_set($batch);
  drush_backend_batch_process();
}

/**
 * Release holds on Shipwire orders.
 *
 * Only updates Shipwire orders that have not been marked delivered in our DB.
 */
function drush_lulzbot_store_release_holds() {
  module_load_include('inc', 'lulzbot_store');
  $shipwire_orders = db_query('SELECT * FROM lulzbot_store_shipwire_orders WHERE release_hold=1 AND processing_release=0')->fetchAllAssoc('shipwire_order_id');
  $count = count($shipwire_orders);
  watchdog('lulzbot_store', 'Found !number :order waiting for hold release', array('!number' => $count, ':order' => $count != 1 ? 'orders' : 'order'));
  foreach ($shipwire_orders as $shipwire_order) {
    $order = commerce_order_load($shipwire_order->commerce_order_id);
    if (!$order) {
      $order = new stdClass();
      $order->order_number = $shipwire_order->commerce_order_id;
    }
    lulzbot_store_shipwire_order_release_hold($order, $shipwire_order);
  }
}

/**
 * Release
 */
function lulzbot_store_drush_release_hold() {
  drush_log(__FUNCTION__, 'ok');
}

/**
 * Cleanup old entries in lulzbot_store_data.
 */
function drush_lulzbot_store_cleanup_data() {
  $old = strtotime('-6 hours');
  db_delete('lulzbot_store_data')
    ->condition('timestamp', $old, '<=')
    ->execute();
}
