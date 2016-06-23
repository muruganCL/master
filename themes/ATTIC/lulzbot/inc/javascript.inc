<?php
/**
 * @file
 * JS related preprocessing
 */

/**
 * Preprocess JavaScript.
 */
function lulzbot_js_alter(&$javascript) {
  $debug = variable_get('js_debug', array());
  $javascript['settings']['data'][] = array('js_debug' => $debug);
  $js_not_minifed = variable_get('js_not_minifed', FALSE);

  // replace with minified versions
  foreach ($javascript as $key => $data) {
    if (!$js_not_minifed) {
      if (preg_match('/^(sites|profiles|modules|misc).+\.js$/', $key) && !preg_match('/^build\/js/', $key) && !preg_match('/\.min\.js$/', $key)) {
        // skip jquery_update
        if (strpos($key, 'jquery_update')) {
          continue;
        }

        // change the build path if the files exist.
        $file_exists = file_exists(DRUPAL_ROOT . '/build/js/' . $data['data']);
        if (isset($javascript[$key]['data']) && $file_exists) {
          $javascript[$key]['data'] = 'build/js/' . $data['data'];
        }
      }
    }
  }
}
