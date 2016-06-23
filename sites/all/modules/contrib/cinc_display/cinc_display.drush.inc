<?php
/**
 * Implements hook_drush_command().
 */
function cinc_display_drush_command() {

  $items['apply-display-settings'] = array(
    'description' => 'Apply the display settings',
    'aliases' => array('ads'),
  );

  return $items;
}

/**
 * Callback for the re-deploy command
 */
function drush_cinc_display_apply_display_settings() {
  drush_log(t('Applying display settings'), 'ok');
  module_invoke_all('cinc_display_apply');
}
