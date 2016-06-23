<?php

/**
 * Implements hook_rules_action_info().
 */
function commerce_signifyd_rules_action_info() {
  return array(
    'commerce_signifyd_submit_case' => array(
      'label' => t('Submit case to Signifyd'),
      'group' => t('Commerce Signifyd'),
      'base' => 'commerce_signifyd_action_submit_case',
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
 * Submit a new case to signifyd for this order.
 */
function commerce_signifyd_action_submit_case($order) {
  if (variable_get('signifyd_api_key', '') && variable_get('signifyd_api_url', '')) {
    $data = commerce_signifyd_get_data_from_order($order);
    if (!variable_get('commerce_signifyd_debug_only', FALSE)) {
      $response = SignifydApi::submit_case($data);
      module_invoke_all('commerce_signifyd_case_submitted', $order, $response);
    }
    watchdog('commerce_signifyd', 'Signifyd case submitted for order :order: :response', array(':order' => $order->order_number, ':response' => json_encode($response)), WATCHDOG_NOTICE);
    return;
  }
  watchdog('commerce_signifyd', 'Signifyd case not submitted for order :order. Missing authentication details.', array(':order' => $order->order_number), WATCHDOG_NOTICE);
}
