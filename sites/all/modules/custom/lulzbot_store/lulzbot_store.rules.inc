<?php

/**
 * Implements hook_rules_event_info().
 */
function lulzbot_store_rules_event_info() {
  return array(
    'lulzbot_store_shipwire_orders_updated' => array(
      'label' => t('Order status updated from Shipwire'),
      'group' => t('Lulzbot Store'),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function lulzbot_store_rules_condition_info() {
  return array(
    'lulzbot_store_user_has_location' => array(
      'label' => t('User has a saved location'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_condition_user_has_location',
    ),
    'lulzbot_store_product_available' => array(
      'label' => t('Product available for user location'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_condition_product_available',
      'parameter' => array(
        'commerce_product' => array(
          'type' => 'commerce_product',
          'label' => t('Product'),
        ),
      ),
    ),
    'lulzbot_store_order_is_us_order' => array(
      'label' => t('Order is shipping to the US'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_condition_order_is_us',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),
    'lulzbot_store_order_is_can_order' => array(
      'label' => t('Order is shipping to the CAN'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_condition_order_is_can',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),

    'lulzbot_store_order_user_has_company' => array(
      'label' => t('Order user is associated with a company'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_order_user_has_company',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),

    'lulzbot_store_product_owner_has_compay' => array(
      'label' => t('Line item user is associated with a company'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_product_owner_has_compay',
      'parameter' => array(
        'commerce_line_item' => array(
          'type' => 'commerce_line_item',
          'label' => t('Line Item'),
        ),
      ),
    ),

    // condition not used in rules and doesn't quite work correctly with rules
    // 'lulzbot_store_order_country' => array(
    //   'label' => t('Order shipping country'),
    //   'group' => t('Lulzbot Store'),
    //   'base' => 'lulzbot_store_condition_order_country',
    //   'parameter' => array(
    //     'commerce_order' => array(
    //       'type' => 'commerce_order',
    //       'label' => t('Order'),
    //     ),
    //     'countries' => array(
    //       'type' => 'list',
    //       'label' => t('Countries'),
    //       'options list' => 'lulzbot_store_condition_order_countries',
    //     ),
    //   ),
    // ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function lulzbot_store_rules_action_info() {
  return array(
    'lulzbot_store_disable_add_to_cart' => array(
      'label' => t('Disable the add to cart button'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_disable_add_to_cart',
    ),

    'lulzbot_store_show_unavailable' => array(
      'label' => t('Show add to cart button as unavailable'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_product_unavailable',
    ),

    'lulzbot_store_place_us_shipwire_orders' => array(
      'label' => t('Place US Shipwire orders'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_place_shipwire_order',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),

    'lulzbot_store_place_intl_shipwire_orders' => array(
      'label' => t('Place International Shipwire orders'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_place_shipwire_order',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),

    'lulzbot_store_unhold_shipwire_orders' => array(
      'label' => t('Unhold Shipwire orders'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_unhold_shipwire_orders',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),

    'lulzbot_store_action_capture_payment' => array(
      'label' => t('Capture payment'),
      'group' => t('Lulzbot Store'),
      'base' => 'lulzbot_store_action_capture_payment',
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),
  );
}

/**
 * Disable the add to cart button.
 *
 * This function will disable the add to cart button. The JS in js/location.js
 * will hide it.
 */
function lulzbot_store_action_disable_add_to_cart() {
  global $stock_cart_check_data;

  // add a class to the submit button to mark it as disabled
  if (!isset($stock_cart_check_data['form']['submit']['#attributes'])) {
    $stock_cart_check_data['form']['submit']['#attributes'] = array();
  }
  if (!isset($stock_cart_check_data['form']['submit']['#attributes']['class'])) {
    $stock_cart_check_data['form']['submit']['#attributes']['class'] = array();
  }
  $stock_cart_check_data['form']['submit']['#attributes']['class'][] = 'form-button-disabled';

  // Originally this rule disabled the form button, but this means the form has
  // to be reloaded for the button to work again. Since we are showing/enabling
  // the button in JavaScript this won't work.
  // $stock_cart_check_data['form']['submit']['#disabled'] = 'disabled';
  $stock_cart_check_data['form']['#attributes']['class']['stock'] = 'disabled';
}

/**
 * Disable the add to cart button.
 *
 * This function will disable the add to cart button. The JS in js/location.js
 * will hide it.
 */
function lulzbot_store_action_product_unavailable() {
  global $stock_cart_check_data;
  $stock_cart_check_data['form']['submit']['#disabled'] = 'disabled';
  $stock_cart_check_data['form']['submit']['#value'] = t('Unavailable');
  $stock_cart_check_data['form']['#attributes']['class']['stock'] = 'unavailable';
}

/**
 * Place Shipwire order.
 *
 * Process and place one or multiple shipwire order(s) based on various
 * configurations.
 *
 * @param object $order
 *   A commerce order.
 */
function lulzbot_store_action_place_shipwire_order($order) {
  module_load_include('inc', 'lulzbot_store');
  lulzbot_store_place_shipwire_order($order);
}

/**
 * Place Shipwire order(s) for US order.
 *
 * Shipwire orders for US orders have a few extra steps:
 *
 * - Printers and other items are shipped from separate warehouses, so mixed
 *   orders will require multiple shipwire orders.
 * - Orders over $50 have free shipping in the US. This affects placing orders
 *   because the shipping level needs to be passed in with the order. This is
 *   also complicated by splitting it up.
 *
 * @param object $order
 *   A Commerce Order.
 */
function lulzbot_store_action_place_us_shipwire_orders($order) {
  module_load_include('inc', 'lulzbot_store');
  $api = shipwire_api_request();

  // get the warehouses that can be used for this order. This may not be
  // necessary because the US orders have a set of rules about which warehouses
  // are used for printers vs. everything else.
  $warehouses = lulzbot_store_get_shipwire_warehouses_for_order($order);

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

  // get the Shipwire warehouses
  $shipwire_warehouses = shipwire_api_warehouses();
  if ($shipping_code === 'LULZBOT_STORE_FREE_SHIPPING') {
    // the user gets free shipping for this order, but we still need to send a
    // valid shipping service level over with the orders. To get this, we will
    // send rate requests for each shipwire order.
    $profile = stools_field_value($order, 'commerce_customer_shipping', LANGUAGE_NONE, array('key' => 'profile_id'));
    $profile = commerce_customer_profile_load($profile);

    if ($has_printer) {
      $rates = shipwire_api_get_default_rates_for_order($order, $profile, $printer_line_items);
      $response = $api->post()->rate($rates[0]);
      if (!$response->isError()) {
        // find the cheapest rate.
        if (isset($response->resource->rates)) {
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
            $printer_shipping_code = $code;
          }
        }
        else {
          watchdog('lulzbot_store', 'Unable to get the shipping rates for the printer portion of a US order that receives free shipping', array(), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
        }
      }
      else {
        watchdog('lulzbot_store', 'Unable to get the shipping rates for the printer portion of a US order that receives free shipping: !order', array('!order' => $order->order_number), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
      }
    }

    if ($has_other_items) {
      $rates = shipwire_api_get_default_rates_for_order($order, $profile, $non_printer_line_items);
      // unset($rates['options']['warehouseArea']);
      // $rates['options']['warehouseId'] = $shipwire_warehouses['Philadelphia'];
      // dd($rates);
      $response = $api->post()->rate($rates[0]);
      if (!$response->isError()) {
        // find the cheapest rate.
        if (isset($response->resource->rates)) {
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
            $other_shipping_code = $code;
          }
        }
        else {
          watchdog('lulzbot_store', 'Unable to get the shipping rates for the non printer portion of a US order that receives free shipping', array(), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
        }
      }
      else {
        watchdog('lulzbot_store', 'Unable to get the shipping rates for the non printer portion of a US order that receives free shipping: !order', array('!order' => $order->order_number), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
      }
    }
  }

  // figure out what kind of orders we may need to make for this order based
  // on type of products within the order.
  $orders = array();
  if ($has_printer && !$has_other_items) {
    // there is only a printer, so we only need to send a Shipwire order to
    // the Chicago warehouse
    $shipwire_order = lulzbot_store_get_shipwire_order($order, $line_items, $shipwire_warehouses['Chicago'], $printer_shipping_code);
    $orders[] = $shipwire_order;
  }
  elseif ($has_other_items && !$has_printer) {
    // there is only non-printer items so we should be able to send the order
    // to the Philadelphia warehouse
    $shipwire_order = lulzbot_store_get_shipwire_order($order, $line_items, $shipwire_warehouses['Philadelphia'], $other_shipping_code);
    $orders[] = $shipwire_order;
  }
  elseif ($has_printer && $has_other_items) {
    // this order has both types of items, so we need to make two Shipwire
    // orders to multiple warehouses.
    // TODO figure out how to do mixed shipping codes
    $orders[] = lulzbot_store_get_shipwire_order($order, $non_printer_line_items, $shipwire_warehouses['Philadelphia'], $other_shipping_code, 'other');
    $orders[] = lulzbot_store_get_shipwire_order($order, $printer_line_items, $shipwire_warehouses['Chicago'], $printer_shipping_code, 'printers');
  }

  // flag this as debuggable if the option is set.
  if (variable_get('lulzbot_store_debug_shipwire_orders', FALSE)) {
    $api->debug();
  }

  // loop through the order(s) we create above.
  $order_count = 0;
  foreach ($orders as $shipwire_order) {
    $response = $api->post()->orders($shipwire_order);
    if ($response->isError()) {
      drupal_set_message(t('There was an error creating this order.'), 'error');
      watchdog('lulzbot_store', 'Error creating Shipwire order', array(), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
      continue;
    }

    // save order info into our order-shipwire-order table
    foreach ($response->resource->items as $shipwire_order_info) {
      lulzbot_store_save_shipwire_order($order, $shipwire_order_info);
      $order_count++;
    }
  }
  watchdog(
    'lulzbot_store',
    'Shipwire !orders created for order !num using ' . __FUNCTION__,
    array(
      '!orders' => format_plural($order_count, 'order', 'orders'),
      '!num' => $order->order_number,
    ),
    WATCHDOG_INFO
  );
}

/**
 * Place Shipwire orders for International orders.
 *
 * International orders place a single order into the Shipwire system.
 *
 * @param object $order
 *   A commerce order.
 */
function lulzbot_store_action_place_intl_shipwire_orders($order) {
  module_load_include('inc', 'lulzbot_store');
  $api = shipwire_api_request();

  // get the warehouses that can be used for this order.
  $warehouses = lulzbot_store_get_shipwire_warehouses_for_order($order);

  // get the product line items for this order
  $line_items = lulzbot_store_get_order_line_items($order);
  $shipping_code = shipwire_api_get_shipping_code_from_order($order);

  // build out the order details that we will send to Shipwire.
  $shipwire_order = lulzbot_store_get_shipwire_order($order, $line_items, $warehouses[0], $shipping_code);

  // flag this as debuggable if the option is set.
  if (variable_get('lulzbot_store_debug_shipwire_orders', FALSE)) {
    $api->debug();
  }

  // send the request
  $response = $api->post()->orders($shipwire_order);
  if ($response->isError()) {
    drupal_set_message(t('There was an error creating this order.'), 'error');
    watchdog('lulzbot_store', 'Error creating Shipwire order', array(), WATCHDOG_ERROR, l(t('Order'), 'admin/commerce/orders/' . $order->order_number));
    return;
  }

  // save order info
  $orders = 0;
  foreach ($response->resource->items as $shipwire_order_info) {
    lulzbot_store_save_shipwire_order($order, $shipwire_order_info);
    $orders++;
  }

  watchdog('lulzbot_store', 'Shipwire !orders created for order !num using ' . __FUNCTION__, array('!orders' => format_plural($orders, 'order', 'orders'), '!num' => $order->order_num), WATCHDOG_INFO);
}

/**
 * Update the shipwire orders so that they are not held.
 *
 * This will attempt to release holds on the orders. If the order is processing
 * still on shipwire, this may be deferred and handled via cron.
 */
function lulzbot_store_action_unhold_shipwire_orders($order) {
  module_load_include('inc', 'lulzbot_store');

  watchdog('lulzbot_store', 'Attempting to release holds for order !order', array('!order' => $order->order_number), WATCHDOG_NOTICE, l(t('Shipwire'), 'admin/commerce/orders/' . $order->order_number));

  // find shipwire orders for this commerce order
  $shipwire_orders = lulzbot_store_get_shipwire_order_data(array('order' => $order->order_number));
  foreach ($shipwire_orders as $shipwire_order) {
    // update the shipwire release_hold flag in the DB.
    db_update('lulzbot_store_shipwire_orders')
      ->fields(array('release_hold' => 1))
      ->condition('shipwire_order_id', $shipwire_order->shipwire_order_id)
      ->execute();

    lulzbot_store_shipwire_order_release_hold($order, $shipwire_order);
  }
}

/**
 * Check if the product is available.
 */
function lulzbot_store_condition_product_available($product) {
  module_load_include('inc', 'lulzbot_store');
  module_load_include('inc', 'lulzbot_store', 'lulzbot_store.availability');
  $availability = lulzbot_store_product_availability($product->sku);
  $location = lulzbot_store_user_country();
  if ($location && in_array($location, array_keys($availability)) && $availability[$location] > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Check if the user has a saved location.
 */
function lulzbot_store_condition_user_has_location() {
  module_load_include('inc', 'lulzbot_store');

  $location = lulzbot_store_user_location();
  if ($location !== FALSE) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Check if the order is shipping to Canada.
 */
function lulzbot_store_condition_order_is_can($order) {
  module_load_include('inc', 'lulzbot_store');
  return in_array(lulzbot_store_get_order_country($order), array('CA', 'CAN'));
}

/**
 * Check if the order is shipping to the United States.
 */
function lulzbot_store_condition_order_is_us($order) {
  module_load_include('inc', 'lulzbot_store');
  return in_array(lulzbot_store_get_order_country($order), array('US', 'USA'));
}

/**
 * Check the country of this order against other orders.
 */
function lulzbot_store_condition_order_country($order, $countries) {
  module_load_include('inc', 'lulzbot_store');
  $country = lulzbot_store_get_order_country($order);
  return in_array($country, $countries);
}

/**
 * Return the list of availabile countries.
 */
function lulzbot_store_condition_order_countries() {
  module_load_include('inc', 'lulzbot_store');
  return lulzbot_store_get_countries();
}

/**
 * Capture the payment.
 *
 * Attempt to capture payment on an order if the order still has a balance.
 */
function lulzbot_store_action_capture_payment($order) {
  // only proceed if there is a balance left on this order.
  $balance = commerce_payment_order_balance($order);
  if ($balance && isset($balance['amount']) && $balance['amount'] > 0) {
    $query = new EntityFieldQuery();
    $transactions = $query->entityCondition('entity_type', 'commerce_payment_transaction')
      ->propertyCondition('order_id', $order->order_number, '=')
      ->execute();
    if ($transactions && isset($transactions['commerce_payment_transaction'])) {
      $transaction_ids = array_keys($transactions['commerce_payment_transaction']);
      $transaction_id = array_shift($transaction_ids);
      $transaction = commerce_payment_transaction_load($transaction_id);
      $payment_method = commerce_payment_method_instance_load($transaction->instance_id);

      if ($payment_method['method_id'] === 'paypal_wpp') {
        lulzbot_store_action_capture_payment__paypal_wpp($order, $transaction, $balance, $payment_method);
      }
      else {
        watchdog('lulzbot_store', 'Unknown payment method for late capture of payment: :method. Cannot capture payment.', array(':method' => $payment_method), WATCHDOG_ERROR);
      }
    }
  }
}

/**
 * Paypal WPP specific payment capture.
 *
 * Copied from the commerce_paypal_wpp module.
 */
function lulzbot_store_action_capture_payment__paypal_wpp($order, $transaction, $balance, $payment_method) {
  // Convert the balance to the transaction currency.
  if ($balance['currency_code'] != $transaction->currency_code) {
    $balance['amount'] = commerce_currency_convert($balance['amount'], $balance['currency_code'], $transaction->currency_code);
    $balance['currency_code'] = $transaction->currency_code;
  }

  $amount = $transaction->amount;
  if ($balance['amount'] > 0 && $balance['amount'] < $transaction->amount) {
    $amount = $balance['amount'];
  }

  $amount = commerce_currency_amount_to_decimal($amount, $transaction->currency_code);
  $authorization_valid = TRUE;

  // If the original authorization was more than 3 days ago, PayPal's honor
  // period is over and a reauthorization is required before capturing.
  if (REQUEST_TIME - $transaction->created > 86400 * 3) {
    // Build a name-value pair array for the reauthorization.
    $nvp = array(
      'METHOD' => 'DoReauthorization',
      'AUTHORIZATIONID' => $transaction->remote_id,
      'AMT' => commerce_paypal_price_amount($transaction->amount, $transaction->currency_code),
      'CURRENCYCODE' => $transaction->currency_code,
    );

    // Submit the reauthorization request.
    $response = commerce_paypal_api_request($payment_method, $nvp, $order);
    $transaction->payload[REQUEST_TIMESTAMP . '-reauthorization'] = $response;

    // If the response contains an authorization ID...
    if (!empty($response['AUTHORIZATIONID'])) {
      // Update the original transaction with the new ID to use when capturing.
      $transaction->remote_id = $response['AUTHORIZATIONID'];
    }
    else {
      // Otherwise do not allow the capture to proceed.
      $transaction->message .= '<br />' . t('Reauthorization failed: @time', array('@time' => format_date(REQUEST_TIME, 'short')));
      $authorization_valid = FALSE;

      // Display a failure message on the redirect.
      // drupal_set_message(t('PayPal requires a reauthorization before capture after 3 days have passed since the initial authorization.'), 'error');
      // drupal_set_message(t('Reauthorization failed with the following error, so the transaction could not capture and will remain in a pending status.'), 'error');
      // drupal_set_message(check_plain($response['L_LONGMESSAGE0']), 'error');
      watchdog(
        'lulzbot_store',
        'There was an error reauthorizing the payment transaction for order :order. Error: :error',
        array(
          ':order' => $order->order_number,
          ':error' => $response['L_LONGMESSAGE0'],
        ),
        WATCHDOG_ERROR,
        l(t('Order'), 'admin/commerce/orders/' . $order->order_number)
      );
      return;
    }
  }

  // If the authorization is valid or successfully reauthorized...
  if ($authorization_valid) {
    // Determine the remaining balance if the capture is successful.
    $transaction_balance = $transaction->amount - commerce_currency_decimal_to_amount($amount, $transaction->currency_code);

    // Prepare a name-value pair array to capture the requested amount.
    $nvp = array(
      'METHOD' => 'DoCapture',
      'AUTHORIZATIONID' => $transaction->remote_id,
      'AMT' => $amount,
      'CURRENCYCODE' => $transaction->currency_code,
      'COMPLETETYPE' => $transaction_balance > 0 ? 'NotComplete' : 'Complete',
    );

    // Submit the capture request request to PayPal.
    $response = commerce_paypal_api_request($payment_method, $nvp, $order);
    $transaction->payload[REQUEST_TIME . '-capture'] = $response;

    switch ($response['ACK']) {
      case 'SuccessWithWarning':
      case 'Success':
        // drupal_set_message(t('Prior authorization captured successfully.'));

        // If this capture did not complete the authorization and subsequent
        // captures can be processed against it, create a follow-up transaction
        // to represent the remaining authorization amount.
        if ($nvp['COMPLETETYPE'] == 'NotComplete') {
          $new_transaction = clone($transaction);
          unset($new_transaction->transaction_id, $new_transaction->revision_id);
          $new_transaction->amount = $transaction_balance;
          commerce_payment_transaction_save($new_transaction);

          // drupal_set_message(t("A follow-up transaction was made to represent the remaining authorization amount that can be captured within PayPal's allowed time limit."));
        }

        // Update the original transaction amount to the actual capture amount,
        // its remote ID to the capture's transaction ID, and its statuses to
        // indicate successful payment.
        $transaction->amount = commerce_currency_decimal_to_amount($amount, $transaction->currency_code);
        $transaction->remote_id = $response['TRANSACTIONID'];
        $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
        $transaction->remote_status = $response['PAYMENTSTATUS'];

        // Note the capture in the transaction message.
        $transaction->message .= '<br />' . t('Captured: @date', array('@date' => format_date(REQUEST_TIME, 'short')));
        watchdog(
          'lulzbot_store',
          'Payment was captured for order :order via the capture payment rule',
          array(
            ':order' => $order->order_number,
          ),
          WATCHDOG_NOTICE,
          l(t('Order'), 'admin/commerce/orders/' . $order->order_number)
        );

        // update order status
        commerce_order_status_update($order, 'processing_shipping', FALSE, TRUE, 'Captured payment, ship order');
        break;

      default:
        // Display an error message but leave the transaction pending.
        // drupal_set_message(t('Prior authorization capture failed, so the transaction will remain in a pending status.'), 'error');
        // drupal_set_message(check_plain($response['L_LONGMESSAGE0']), 'error');
        watchdog(
          'lulzbot_store',
          'Payment capture failed for the payment transaction for order :order. Error: :error',
          array(
            ':order' => $order->order_number,
            ':error' => $response['L_LONGMESSAGE0'],
          ),
          WATCHDOG_ERROR,
          l(t('Order'), 'admin/commerce/orders/' . $order->order_number)
        );
        break;
    }
  }

  // Save the updated original transaction.
  commerce_payment_transaction_save($transaction);
}

/**
 * Condition to check if the order user is part of a company.
 */
function lulzbot_store_order_user_has_company($order, $settings) {
  if (isset($settings['companies']) && $settings['companies']) {
    $user = user_load($order->uid);
    foreach ($settings['companies'] as $company) {
      if (stools_field_contains_value($user, 'field_user_companies', $company)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Condition to check if the order user is part of a company.
 */
function lulzbot_store_product_owner_has_compay($line_item, $settings) {
  if (isset($settings['companies']) && $settings['companies']) {
    $order = commerce_order_load($line_item->order_id);
    return lulzbot_store_order_user_has_company($order, $settings);
  }
  return FALSE;
}
