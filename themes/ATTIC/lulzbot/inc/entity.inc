<?php

/**
 * Implements hook_preprocess_entity().
 */
function lulzbot_preprocess_entity(&$vars) {
  if ($vars['entity_type'] === 'bean') {
    if ($vars['bean']->type === 'main_call_to_action') {
      $wrapper = entity_metadata_wrapper('bean', $vars['bean']);

      $vars['classes_array'][] = 'call-to-action';
      if (!empty($vars['field_main_cta_image'])) {
        $vars['cta_bg'] = image_style_url('large', $wrapper->field_main_cta_image->value()['uri']);
      }
    }
  }
}
