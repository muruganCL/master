<?php
/**
 * Webhooks admin page.
 */
function shipwire_webhooks_admin($form, &$form_state) {
  shipwire_webhooks_update_webhooks(TRUE);
  $webhooks = shipwire_webhooks_get_webhooks();

  $formui = new FormUI($form);

  $formui
    ->add('intro', t('<p>Below are the webhooks registered with Shipwire.</p>'))
    ->add('actions', '<ul class="action-links"><li>' . l(t('Add webhook'), 'admin/shipwire/settings/webhooks/add') . '</li></ul>')
    ->add(
      'webhooks',
      $formui->table(array('ID', 'Topic', 'Calls', 'Last Called'), $webhooks)
        ->setOption('empty', t('No webhooks have been registered yet.'))
    );

  return $formui->generate();
}

/**
 * Add a web hook.
 */
function shipwire_webhooks_admin_add($form, &$form_state) {
  shipwire_webhooks_update_webhooks(TRUE);
  $webhooks = shipwire_webhooks_get_webhooks();

  $topics = array(
    'orders' => t('Orders'),
    'tracking' => t('Tracking'),
  );

  if (!empty($webhooks)) {
    // reduce the topic options by hooks we have already added.
  }

  if (!$topics) {
    drupal_set_message(t('There are no available topics to use; All webhooks have been registered.'), 'status');
    drupal_goto('admin/shipwire/settings/webhooks');
    return;
  }

  $formui = new FormUI($form);

  $keys = array_keys($topics);
  $first_key = array_shift($keys);
  $formui
    ->add('topic', $formui->radios($topics)->setOption('title', 'Topic')->setOption('default_value', $first_key))
    ->add('submit', $formui->submit('Add webhook'))
    ->add('cancel', l(t('Cancel'), 'admin/shipwire/settings/webhooks'));
  return $formui->generate();
}

/**
 * Submit handler for adding webhooks.
 */
function shipwire_webhooks_admin_add_submit($form, &$form_state) {
  $shipwire = shipwire_api_request();
  $url = url('shipwire_webhooks');
  $response = $shipwire->post()->webhooks(array('topic' => $form_state['values']['topic'], 'url' => $url));

  // check if there was an error
  if ($response->isError()) {
    drupal_set_message(t('There was an error adding the webhook. Error: %error', array('%error' => implode('. ', $response->errors))), 'error');
    drupal_goto('admin/shipwire/settings/webhooks/add');
    return;
  }

  drupal_set_message(t('Webhook created'), 'status');
  drupal_goto('admin/shipwire/settings/webhooks');
}

/**
 * List webhook secrets.
 */
function shipwire_webhooks_secrets_admin($form, &$form_state) {
  shipwire_webhooks_update_secrets(TRUE);
  $secrets = shipwire_webhooks_get_secrets();

  foreach (array_keys($secrets) as $id) {
    $secrets[$id][] = l(t('Delete'), 'admin/shipwire/settings/webhook_secrets/delete/' . $id);
  }

  $formui = new FormUI($form);
  $formui
    ->add('description', '<p>List of secrets added for this shipwire account.</p>')
    ->add('actions', '<ul class="action-links"><li>' . l(t('Add secret'), 'admin/shipwire/settings/webhook_secrets/add') . '</li></ul>')
    ->add(
      'secrets',
      $formui
        ->table(array('ID', 'Secret', ''), $secrets)
        ->setOption('empty', t('No secrets have been added yet.'))
    );
  return $formui->generate();
}

/**
 * Add webhook secret.
 */
function shipwire_webhooks_secrets_admin_add($form, &$form_state) {
  $formui = new FormUI($form);

  $formui
    ->add('intro', t('<p>Secrets are used to verify incoming messages to the webhook endpoints. It is strongly recommended to have at least one secret when using webhooks.</p>'))
    ->add('submit', $formui->submit(t('Create secret')))
    ->add('cancel', l(t('Cancel'), 'admin/shipwire/settings/webhook_secrets'));

  return $formui->generate();
}

/**
 * Submit handler for adding secrets.
 */
function shipwire_webhooks_secrets_admin_add_submit($form, &$form_state) {
  $shipwire = shipwire_api_request();
  $response = $shipwire->post()->secret();
  drupal_set_message(t('Secret created'), 'status');
  drupal_goto('admin/shipwire/settings/webhook_secrets');
}

/**
 * Delete secret form.
 */
function shipwire_webhooks_secrets_admin_delete($form, &$form_state, $secret_id) {
  $formui = new FormUI($form);
  $formui->add('intro', t('<p>Do you really wish to delete this secret?</p>'))
    ->add('secret_id', $formui->hidden(intval($secret_id)))
    ->add('delete', $formui->submit('Delete secret'))
    ->add('cancel', l(t('Cancel'), 'admin/shipwire/settings/webhook_secrets'));
  return $formui->generate();
}

/**
 * Submit handler for the delete secret form.
 */
function shipwire_webhooks_secrets_admin_delete_submit($form, &$form_state) {
  $shipwire = shipwire_api_request();
  if (isset($form_state['values']['secret_id'])) {
    $response = $shipwire->delete()->secret(intval($form_state['values']['secret_id']));
  }
  drupal_set_message(t('Secret deleted. If the key is still present, this may be an issue with the Shipwire API.'), 'status');
  drupal_goto('admin/shipwire/settings/webhook_secrets');
}
