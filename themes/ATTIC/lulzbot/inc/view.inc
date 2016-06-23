<?php

/**
 * template_preprocess_views_view
 */
function lulzbot_preprocess_views_view(&$vars) {

  if ($vars['name'] === 'homepage_news') {
    if ($vars['view']->current_display === 'attachment_1') {
      $vars['classes_array'][] = 'featured-promo';
    }
    if ($vars['view']->current_display === 'block') {
      $vars['classes_array'][] = 'promos';
    }
  }

  if ($vars['name'] === 'learn') {
    $vars['classes_array'][] = 'learn-promos';
  }

  if ($vars['name'] === 'support') {
    $vars['classes_array'][] = 'support-list';
  }

  if ($vars['name'] === 'merchandise') {
    $vars['classes_array'][] = 'clearfix';
  }
}
