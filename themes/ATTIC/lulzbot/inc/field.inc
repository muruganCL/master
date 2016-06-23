<?php

/**
 * @file
 * Field hooks.
 */

/**
 * Implements hook_preprocess_field().
 */
function lulzbot_preprocess_field(&$vars) {

  // Set shortcut variables. Hooray for less typing!
  $name = $vars['element']['#field_name'];
  $bundle = $vars['element']['#bundle'];
  $mode = $vars['element']['#view_mode'];
  $classes = &$vars['classes_array'];
  $title_classes = &$vars['title_attributes_array']['class'];
  $content_classes = &$vars['content_attributes_array']['class'];
  $item_classes = array();

  // Global field styles.
  $classes = array(
    'field',
    'field--' . str_replace('_', '-', $name),
  );
  $title_classes = array('field-label');
  $content_classes = array('field-items');
  $item_classes = array('field-item');

  // Handle inline label classes.
  if (!$vars['label_hidden'] && $vars['element']['#label_display'] == 'inline') {
    $classes[] = 'field--inline-label';
  }

  // Uncomment the lines below to see variables you can use to target a field.
  // This requires http://drupal.org/project/devel to be installed.
  // dpm($name, 'Name:');
  // dpm($bundle, 'Bundle:');
  // dpm($mode, 'Mode:');

  // Example: Using an alternative theme function.
  // if($name == 'field_tags') {
  //   $vars['theme_hook_suggestions'][] = 'field__custom_separated';
  // }

  switch ($name) {
    case 'commerce_price':
      if (
        $vars['element']['#object']->display_context['view_mode'] === 'full' ||
        $vars['element']['#object']->display_context['view_mode'] === 'compare' ||
        $vars['element']['#object']->display_context['view_mode'] === 'node_full'
        ) {
        $price = explode('$', $vars['items'][0]['#markup']);
        if (isset($vars['element']['#object']->commerce_price[LANGUAGE_NONE][0]['currency_code'])) {
          $currency_code = $vars['element']['#object']->commerce_price[LANGUAGE_NONE][0]['currency_code'];
        }
        $currency_sym = (isset($currency_code)) ? commerce_currency_get_symbol($currency_code) : 'US$';
        $dec = explode('.', $price[1]);
        $vars['items'][0]['#markup'] = '<span class="symbol">' . $currency_sym . '</span><span class="dollars">' . $dec[0] . '</span><span class="cents">' . $dec[1] . '</span>';

        $content_classes[] = 'price--large';
      } else if ($vars['element']['#object']->display_context['view_mode'] === 'feature') {
        $content_classes[] = 'price--small';
      } else {
        $content_classes[] = 'price--gray';
      }
      break;

    case 'field_printer_reviews':
    case 'field_part_reviews':
    case 'field_merchandise_reviews':
    case 'field_tool_head_reviews':
    case 'field_filament_reviews':
      $vars['theme_hook_suggestions'][] = 'field__field_printer_reviews';

      $field_array = array(
        'field_review_quote',
        'field_review_name',
        'field_review_title',
        'field_review_image',
      );
      rows_from_field_collection($vars, $field_array);
      break;
    case 'field_merchandise_alerts':
    case 'field_part_alerts':
    case 'field_printer_alerts':
    case 'field_tool_head_alerts':
    case 'field_filament_alerts':
      $vars['theme_hook_suggestions'][] = 'field__field_merchandise_alerts';

      $field_array = array(
        'field_alert_name',
        'field_alert_message',
      );
      rows_from_field_collection($vars, $field_array);
      break;

    case 'field_printer_fc2_products':
    case 'field_merchandise_related_prods':
    case 'field_part_related_products':
    case 'field_tool_head_related_products':
    case 'field_filament_related_filaments':
      $content_classes[] = 'list--ruled';
      $vars['theme_hook_suggestions'][] = 'field__ul';
      break;

    case 'field_part_project_showcase':
      $content_classes[] = 'list--ruled';
      $content_classes[] = 'carousel';
      $vars['theme_hook_suggestions'][] = 'field__ul';
      break;
    case 'field_part_images':
      if ($mode === 'feature') {
        $vars['theme_hook_suggestions'][] = 'field__first_only';
      }
      break;
    case 'field_filament_compatiblity':
    case 'field_part_compatible_printers':
    case 'field_tool_head_compatiblity':
      $vars['theme_hook_suggestions'][] = 'field__comma';
      break;
    case 'field_store_category_products':
      $vars['label_hidden'] = TRUE;
      $content_classes[] = 'no-bullets';
      $content_classes[] = 'store--products';
      $vars['theme_hook_suggestions'][] = 'field__ul';
      break;
    case 'commerce_customer_address':
      $vars['label_hidden'] = FALSE;
      $vars['label'] = ucwords($vars['element']['#bundle']) . ' Address';
      $vars['theme_hook_suggestions'][] = 'field__label';
      break;
  }

  // Apply odd or even classes along with our custom classes to each item.
  if (isset($vars['items'])) {
    foreach ($vars['items'] as $delta => $item) {
      $vars['item_attributes_array'][$delta]['class'] = $item_classes;
      $striping = $delta % 2 ? 'even' : 'odd';
      $vars['item_attributes_array'][$delta]['class'][] = $striping;
    }
  }

  $preprocesses = array(
    $name,
  );
  center_preprocessors($vars, __FUNCTION__, $preprocesses);
}

/**
 * Preprocess field_printer_display_specs.
 */
function lulzbot_preprocess_field__field_printer_display_specs(array &$vars) {
  $items =& $vars['items'];
  $vars['rows'] = array();

  foreach ($items as $item) {
    $this_item = array_shift($item['entity']['field_collection_item']);
    $this_row = array();
    $this_row[] = $this_item['field_specs_title'][0];
    $this_row[] = $this_item['field_specs_mini_value'][0];
    $this_row[] = $this_item['field_specs_taz_value'][0];

    $this_row[1]['#prefix'] = $this_row[2]['#prefix'] = '<div class="specification">';
    $this_row[1]['#suffix'] = $this_row[2]['#suffix'] = '</div>';

    if ($this_row[1]['#markup'] === 'Yes') {
      $this_row[1]['#prefix'] = '<div class="specification specification--yes">';
    }

    if ($this_row[2]['#markup'] === 'Yes') {
      $this_row[2]['#prefix'] = '<div class="specification specification--yes">';
    }
    $vars['rows'][] = $this_row;
  }
}

/**
 * Creates a simple text rows array from a field collections, to be used in a
 * field_preprocess function.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $field_array
 *   Array of fields to be turned into rows in the field collection.
 */
function rows_from_field_collection(array &$vars, array $field_array) {
  $vars['rows'] = array();
  foreach($vars['element']['#items'] as $key => $item) {
    $entity_id = $item['value'];
    $entity = field_collection_item_load($entity_id);
    $wrapper = entity_metadata_wrapper('field_collection_item', $entity);
    $row = array();
    foreach($field_array as $field){
      $row[$field] = field_view_field('field_collection_item', $entity, $field, 'full');
    }
    $vars['rows'][] = $row;
  }
}

/**
 * Custom implementation of theme_field().
 *
 * Renders a multi-value field as an unordered list.
 * USAGE: $vars['theme_hook_suggestions'][] = 'field__ul';
 */
function lulzbot_field__ul($variables) {
  $output = '';

  // Render the items.
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li> ';
  }

  // Render the ul.
  $output = '<ul ' . $variables['content_attributes'] . '>' . $output . '</ul>';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output = '<h4 class="label">' . $variables['label'] . '</h4> ' . $output;
  }

  return $output;
}

/**
 * Custom implementation of theme_field().
 *
 * Renders a multi-value field with a label.
 * USAGE: $vars['theme_hook_suggestions'][] = 'field__label';
 */
function lulzbot_field__label($variables) {
  $output = '';

  // Render the items.
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<span' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</span> ';
  }

  // Render the ul.
  $output = '<div ' . $variables['content_attributes'] . '>' . $output . '</div>';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output = '<strong class="label">' . $variables['label'] . '</strong> ' . $output;
  }

  return $output;
}

/**
 * Custom implementation of theme_field().
 *
 * Renders a multi-value field as a comma separated list.
 * USAGE: $vars['theme_hook_suggestions'][] = 'field__comma';
 */
function lulzbot_field__comma($variables) {
  $output = '';

  // Render the items.
  $len = (count($variables['items']) - 1);
  foreach ($variables['items'] as $delta => $item) {
    if ($delta === $len) {
      $output .= '<span' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</span> ';
    } else {
      $output .= '<span' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</span>, ';
    }
  }

  // Render the ul.
  $output = '<span ' . $variables['content_attributes'] . '>' . $output . '</span>';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output = '<h4 class="label">' . $variables['label'] . '</h4> ' . $output;
  }

  return $output;
}

/**
 * Custom implementation of theme_field().
 *
 * Renders only the first item.
 * USAGE: $vars['theme_hook_suggestions'][] = 'field__first_only';
 */
function lulzbot_field__first_only($variables) {
  $output = '';

  $output .= drupal_render($variables['item'][0]);

  return $output;
}



function lulzbot_field__commerce_price($variables) {
  $output = '';

  // Render the items.
  foreach ($variables['items'] as $delta => $item) {
    $output .= drupal_render($item);
  }

  // Render the wrapper.
  $output = '<span ' . $variables['content_attributes'] . '>' . $output . '</span>';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output = '<h4 class="label">' . $variables['label'] . '</h4> ' . $output;
  }

  return $output;
}
