<?php
/**
 * Implements hook_default_rules_configuration().
 */
function lulzbot_store_default_rules_configuration() {
  $config = array();

  $rules_path = drupal_get_path('module', 'lulzbot_store') . '/rules';
  $files = file_scan_directory($rules_path, '/\.rule\.json$/');
  foreach ($files as $path => $file) {
    list($name, $extension) = explode('.', $file->name);
    $config[$name] = rules_import(file_get_contents($path));
  }
  return $config;
}
