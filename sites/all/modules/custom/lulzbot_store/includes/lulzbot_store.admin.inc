<?php
/**
 * Administer countries available in the store.
 */
function lulzbot_store_admin_countries() {
  $page = new FormUI();

  $page
    ->add('description', '<p>Use this page to administer the countries available to users when selecting their location and to manage where countries get their products.</p>');

  module_load_include('inc', 'lulzbot_store');
  $countries = lulzbot_store_get_countries(TRUE);
  $countries_config = lulzbot_store_get_countries_config();

  // get the warehouses
  $shipwire = shipwire_api_request();
  $warehouses = drupal_map_assoc($shipwire->cacheable()->getWarehouses());
  array_unshift($warehouses, 'None');

  // build a shared select element
  $status = new FormUISelect(array('enabled' => t('Enabled'), 'hidden' => t('Hidden')));
  $status->setOption('attributes', array('class' => array('country-status')));

  // build a shared warehouse element
  $warehouse = new FormUISelect($warehouses);
  $warehouse
    ->setOption('multiple', TRUE)
    ->setOption('attributes', array('class' => array('warehouses')))
    ->setOption('size', 4);

  $country_options = array();
  foreach ($countries as $country_code => $country) {
    $this_status = $status->generate();
    $this_status['#attributes']['name'] = 'country-status-' . $country_code;
    $this_status['#value'] = $countries_config[$country_code]->hidden ? 'hidden' : 'enabled';

    $this_warehouse = $warehouse->generate();
    $this_warehouse['#attributes']['multiple'] = 'multiple';
    $this_warehouse['#attributes']['name'] = 'warehouse-' . $country_code . '[]';
    $this_warehouse['#value'] = explode(',', trim($countries_config[$country_code]->warehouses));
    $this_country = array(
      'code' => $country_code,
      'country' => $country,
      'status' => array('data' => $this_status),
      'warehouse' => array('data' => $this_warehouse),
    );
    $country_options[] = $this_country;
  }

  $page
    ->add('submit-top', $page->submit('Save'))
    ->add(
      'actions',
      $page->select(array('' => 'Pick an action', 'enable' => 'Enable selected', 'disable' => 'Disable selected', 'all' => 'Enable all warehouses', 'none' => 'Disable all warehouses'))
        ->setOption('attributes', array('id' => 'country-actions', 'disabled' => 'disabled'))
    )
    ->add(
      'countries',
      $page->tableselect(
        array(
          'code' => t('Code'),
          'country' => t('Country'),
          'status' => t('Status'),
          'warehouse' => t('Warehouse')
        ),
        $country_options,
        t('There are no countries.')
      )
        ->wrap('div.countries-table')
        ->setOption('attached', array('js' => array(
          drupal_get_path('module', 'lulzbot_store') . '/js/countries.js' => array()
        )))
    )
    ->add('submit', $page->submit('Save'));

  return $page->generate();
}

/**
 * Submit handler for lulzbot countries admin page.
 */
function lulzbot_store_admin_countries_submit($form, &$form_state) {
  $enabled_countries = array();
  $hidden_countries = array();
  $warehouse_settings = array();
  foreach ($form_state['input'] as $key => $value) {
    if (preg_match('/^country-status-(\w+)$/', $key, $matches)) {
      if ($value === 'enabled') {
        $enabled_countries[] = $matches[1];
        continue;
      }

      $hidden_countries[] = $matches[1];
    }
    elseif (preg_match('/^warehouse-(\w+)$/', $key, $matches)) {

      $warehouses = implode(',', $value);
      if (in_array('0', $value)) {
        $warehouses = 'none';
      }

      if (!isset($warehouse_settings[$warehouses])) {
        $warehouse_settings[$warehouses] = array();
      }
      $warehouse_settings[$warehouses][] = $matches[1];
    }
  }

  if (!empty($enabled_countries)) {
    db_update('lulzbot_store_countries')
      ->fields(array('hidden' => 0))
      ->condition('country_code', $enabled_countries, 'IN')
      ->execute();
  }

  if (!empty($hidden_countries)) {
    db_update('lulzbot_store_countries')
      ->fields(array('hidden' => 1))
      ->condition('country_code', $hidden_countries, 'IN')
      ->execute();
  }

  foreach ($warehouse_settings as $warehouses => $countries) {
    if ($warehouses === 'none') {
      $warehouses = '';
    }
    db_update('lulzbot_store_countries')
      ->fields(array(
        'warehouses' => $warehouses,
      ))
      ->condition('country_code', $countries, 'IN')
      ->execute();
  }

  drupal_set_message(t('Countries settings have been saved.'), 'status');
}

/**
 * Add product availability information to the product form.
 */
function lulzbot_store_admin_add_product_availability(&$form, &$form_state) {
  $formui = new FormUI($form);
  $formui->addFieldset('product_availability', array('title' => 'Product Availability', 'weight' => 100, 'collapsible' => TRUE))
    ->add('product_availability', 'intro', $formui->markup('<p>Below is the availability for this product. Products are marked as available if there are products in the <em>Good</em> column.</p>'));

  $response = shipwire_api_request()
    ->clearCache()
    ->stock(array('sku' => $form['#entity']->sku));

  if ($response->isError()) {
    $formui->add('product_availability', 'error', '<p>There was an error checking availability.</p>');
  }
  else {
    $warehouses = array();
    $headers = array(
      'warehouse' => 'Warehouse',
      'pending' => 'Pending',
      'good' => 'Good',
      'reserved' => 'Reserved',
      'backordered' => 'Backordered',
      'shipping' => 'Shipping',
      'shipped' => 'Shipped',
      'damaged' => 'Damaged',
      'returned' => 'Returned',
      'inreview' => 'In Review',
    );
    $rows = array();
    foreach ($response->resource->items as $item) {
      $rows[] = array(
        'warehouse' => $item->resource->warehouseRegion,
        'pending' => $item->resource->pending,
        'good' => $item->resource->good,
        'reserved' => $item->resource->reserved,
        'backordered' => $item->resource->backordered,
        'shipping' => $item->resource->shipping,
        'shipped' => $item->resource->shipped,
        'damaged' => $item->resource->damaged,
        'returned' => $item->resource->returned,
        'inreview' => $item->resource->inreview,
      );
    }

    $formui->add('product_availability', 'availability', $formui->table($headers, $rows));
  }

  $form = $formui->generate();
}

/**
 * View shipwire order information.
 */
function lulzbot_store_admin_shipwire_view($form, &$form_state, $order) {
  $formui = new FormUI($form);
  $formui->add('intro', '<p>This screen shows details of any shipments associated with this order. The <em>status</em> column is the Shipwire status while the <em>On Hold</em> column is whether or not the LulzBot
    store is holding this item for any reason. In the <em>Releasing</em> column, you can see if the holds on this order are set to be released. The <em>view</em> link will take you to the Shipwire order where you can view more information.</p>');

  $orders = db_query('SELECT * FROM lulzbot_store_shipwire_orders WHERE commerce_order_id=:id', array(':id' => $order->order_number))->fetchAllAssoc('shipwire_order_id');

  $headers = array('Shipwire Order ID', 'Status', 'On Hold', 'Releasing', '');
  $rows = array();
  $endpoint = variable_get('shipwire_server', 'Test');
  $base_url = ($endpoint == 'Test') ? 'https://merchant.beta.shipwire.com/' : 'https://merchant.shipwire.com/';
  foreach ($orders as $order) {
    $link = $base_url . 'merchants/ship/confirm/orderId/' . $order->shipwire_order_id;
    $rows[] = array(
      $order->shipwire_order_id,
      $order->status,
      $order->on_hold ? 'Yes' : 'No',
      $order->release_hold ? 'Yes' : 'No',
      l(t('View'), $link),
    );
  }

  $formui->add('table', $formui->table($headers, $rows)->setOption('empty', 'No shipwire orders have been created for this order.'));

  // get shipping quote if this order is still in process
  if (stools_string_startswith($order->status, 'checkout')) {
    module_load_include('inc', 'lulzbot_store');
    $rates = lulzbot_store_shipwire_api_get_rates_for_order($order, NULL, NULL);
    $formui
      ->addFieldset('shipping', array('title' => 'Shipping Rates'));

    $shipping_headers = array('Type', 'Cost', 'Warehouse');
    $shipping_rows = array();
    commerce_shipping_collect_rates($order);

    foreach ($order->shipping_rates as $rate) {
      $warehouse = '?';

      if (isset($rate->commerce_unit_price[LANGUAGE_NONE][0]['shipwire_api'])) {
        $warehouse = array();
        foreach ($rate->commerce_unit_price[LANGUAGE_NONE][0]['shipwire_api'] as $shipwire_rate) {
          $warehouse[] = $shipwire_rate['warehouse_code'];
        }
        $warehouse = implode(', ', $warehouse);
      }

      $shipping_rows[] = array(
        $rate->line_item_label,
        commerce_currency_amount_to_decimal($rate->commerce_unit_price[LANGUAGE_NONE][0]['amount'], $rate->commerce_unit_price[LANGUAGE_NONE][0]['currency']),
        $warehouse,
      );
    }
    $formui->add('shipping', 'description', '<p>This is the shipping rates for this order:</p>');
    $formui->add('shipping', 'shipping_rates', $formui->table($shipping_headers, $shipping_rows));
  }

  return $formui->generate();
}

/**
 * View signifyd order information.
 */
function lulzbot_store_admin_signifyd($form, &$form_state, $order) {
  $formui = new FormUI($form);
  $formui->add('intro', '<p>This screen displays responses from the Signifyd order verification service. Messages will likely include the case submission information and the any responses for that case.</p>');

  // get any signifyd messages from lulzbot_store_signifyd
  $query = db_select('lulzbot_store_signifyd', 's')->fields('s')->condition('order_id', $order->order_number, '=');
  $messages = $query->execute()->fetchAll();

  $headers = array('Date', 'Message');
  $rows = array();
  foreach ($messages as $message) {
    $message_text = '';
    $data = json_decode($message->response);
    if (isset($data->data, $data->status_message)) {
      $case_data = json_decode($data->data);
      $message_text .= 'Case submission status: ' . check_plain($data->status_message) . '; Case #' . $case_data->investigationId;
    }
    elseif (isset($data->orderId)) {
      $status = check_plain(isset($data->guaranteeDisposition) ? $data->guaranteeDisposition : $data->reviewDisposition);
      $message_text .= 'Case status: ' . $status;
    }
    $rows[] = array(format_date($message->updated), $message_text);
  }

  $formui->add('table', $formui->table($headers, $rows)->setOption('empty', 'No signifyd information has been recorded.'));

  return $formui->generate();
}

/**
 * Administer countries available in the store.
 */
function lulzbot_store_admin_free_countries() {
  $page = new FormUI();

  $page
    ->add('description', '<p>Use this page to administer which countries should have a free shipping option.</p>');

  module_load_include('inc', 'lulzbot_store');
  $countries = lulzbot_store_get_countries(TRUE);
  $countries_config = variable_get('lulzbot_store_free_countries', '');
  $countries_config = array_filter(explode(',', $countries_config));

  // build a shared select element
  $status = new FormUISelect(array('enabled' => t('Enabled'), 'hidden' => t('Hidden')));
  $status->setOption('attributes', array('class' => array('country-status')));

  $country_options = array();
  $selected = array();
  foreach ($countries as $country_code => $country) {
    $enabled = in_array($country_code, $countries_config);
    if ($enabled) {
      $selected[] = $country_code;
    }
    $country_options[$country_code] = $country;
  }

  $page
    ->add(
      'countries',
      $page->select($country_options)
        ->setOption('default_value', $selected)
        ->setOption('multiple', TRUE)
        ->setOption('size', 100)
        ->wrap('div.countries-table')
    )
    ->add('submit', $page->submit('Save'));

  return $page->generate();
}

/**
 * Submit handler for lulzbot countries admin page.
 */
function lulzbot_store_admin_free_countries_submit($form, &$form_state) {
  $enabled_countries = array_values($form_state['values']['countries']);
  if (!empty($enabled_countries)) {
    variable_set('lulzbot_store_free_countries', implode(',', $enabled_countries));
  }
  drupal_set_message(t('Countries settings have been saved.'), 'status');
}

/**
 * Show API configuration.
 *
 * Displays information about what API endpoints this environment is pointed at.
 */
function lulzbot_store_admin_api_configuration() {
  $page = array();

  $rows = array();

  // signifyd information
  $rows[] = ['Signifyd endpoint', l(variable_get('signifyd_api_url'), 'admin/config/services/signifyd')];
  $rows[] = ['Signifyd key', l(variable_get('signifyd_api_key'), 'admin/config/services/signifyd')];

  // shipwire information
  $rows[] = ['Shipwire server', l(variable_get('shipwire_server'), 'admin/shipwire/settings')];

  // "decrypt" the shipwire credentials so we can show where the site is pointed
  // this number if from the shipwire module.
  $app_id = 3048610241825397;
  $account = variable_get('shipwire_account', FALSE);
  $key = trim(preg_replace('/[^0-9]/', '', $app_id), 293570648);
  $len = preg_replace('/[^0-9]/', '', substr($account, 0, 8)) - $key;
  $value_decrypt = base64_decode(substr($account, 8));
  $user = substr($value_decrypt, 0, $len);
  $rows[] = ['Shipwire authorization', l($user, 'admin/shipwire/settings')];

  // paypal wpp
  $config = db_query('SELECT data FROM rules_config WHERE name=:name', array(':name' => 'commerce_payment_paypal_wpp'))->fetchColumn(0);
  $rule_config = json_decode(unserialize($config)->export());
  $rule_config = $rule_config->commerce_payment_paypal_wpp->DO[0]->commerce_payment_enable_paypal_wpp->payment_method->value->settings;
  $rows[] = ['Paypal credit card username', l($rule_config->api_username, 'admin/config/workflow/rules/reaction/manage/commerce_payment_paypal_wpp')];
  $rows[] = ['Paypal credit card server', l($rule_config->server, 'admin/config/workflow/rules/reaction/manage/commerce_payment_paypal_wpp')];

  $config = db_query('SELECT data FROM rules_config WHERE name=:name', array(':name' => 'commerce_payment_paypal_wps'))->fetchColumn(0);
  $rule_config = json_decode(unserialize($config)->export());
  $rule_config = $rule_config->commerce_payment_paypal_wps->DO[0]->commerce_payment_enable_paypal_wps->payment_method->value->settings;
  $rows[] = ['Paypal WPS username', l($rule_config->business, 'admin/config/workflow/rules/reaction/manage/commerce_payment_paypal_wps')];
  $rows[] = ['Paypal WPS server', l($rule_config->server, 'admin/config/workflow/rules/reaction/manage/commerce_payment_paypal_wps')];

  $page['intro'] = array(
    '#type' => 'markup',
    '#markup' => '<p>This page displays the endpoints and relevant settings for API endpoints. You can edit changes by clicking on the value.</p>',
  );
  $page['configuration'] = array(
    '#theme' => 'table',
    '#header' => array('Item', 'Value'),
    '#rows' => $rows,
    '#attributes' => array(),
    '#caption' => '',
    '#colgroups' => array(),
    '#sticky' => FALSE,
    '#empty' => '',
  );

  return $page;
}
