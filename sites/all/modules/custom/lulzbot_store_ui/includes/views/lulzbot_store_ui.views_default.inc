<?php

/**
 * Implements hook_views_default_views().
 *
 * Loads any default views and defines them for the views module.
 */
function lulzbot_store_ui_views_default_views() {
  // Create a path where we can find all included views files.
  $module_path = drupal_get_path('module', 'lulzbot_store_ui');
  $glob_path =  $module_path . '/includes/views/lulzbot_store_ui.*.view.inc';

  // Get an array of any files matching our glob.
  $views = glob($glob_path);

  // Load the view from each file into a view.
  $views = array_map(function ($view_path) {
    include $view_path;
    return $view;
  }, $views);

  // Get an array of those views' names.
  $views_names = array_map(function ($view) { return $view->name; }, $views);

  // Create a new array keyed by view name with the view as its value.
  $views = array_combine($views_names, $views);

  return $views;
}
