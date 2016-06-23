<?php
/**
 * @file
 * Form hooks.
 */

/**
 * Implements hook_form_alter().
 */
function lulzbot_form_alter(&$form, &$form_state, $form_id) {

  // Add placeholder text to a form.
  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = "Search";
  }

  if (strpos($form_id, 'commerce_cart_add_to_cart_form') !== FALSE) {

    if (isset($form['submit']['#disabled']) && $form['submit']['#disabled'] !== 'disabled') {
      $form['submit']['#attributes']['class'][] = 'button--add-to-cart';
    } else {
      $form['submit']['#attributes']['class'][] = 'button--cart';
    }

  }

  if ($form_id === 'views_exposed_form') {

    // parts sorter
    if (
      $form['#id'] === 'views-exposed-form-parts-parts-block' ||
      $form['#id'] === 'views-exposed-form-filament-fila-block' ||
      $form['#id'] === 'views-exposed-form-tool-heads-th-block'
    ) {
      // $form['sort_bef_combine']['#title'] = '';
    }

    if (isset($form['#info']['filter-keys'])) {
      $form['#info']['filter-keys']['label'] = '';
      $form['keys']['#attributes']['placeholder'] = "Search by keyword";
    }

    if (isset($form['#info']['filter-combine'])) {
      $form['#info']['filter-combine']['label'] = '';
      $form['combine']['#attributes']['placeholder'] = "Search by keyword";
    }

    if (isset($form['#info']['filter-title'])) {
      $form['#info']['filter-title']['label'] = '';
      $form['title']['#attributes']['placeholder'] = "Search by title";
    }

    if (!isset($form_state['#combine_param'])) {
      $form_state['#combine_param'] = 'sort_bef_combine';
    }
    // dpm($form);
  }

}

/**
 * Implements hook_select().
 */
function lulzbot_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<div class="select-wrapper"><select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select></div>';
}
