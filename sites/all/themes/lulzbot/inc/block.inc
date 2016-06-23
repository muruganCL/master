<?php
/**
 * @file
 * Block hooks.
 */

/**
 * Implements hook_preprocess_block().
 */
function lulzbot_preprocess_block(&$vars) {

  // Set shortcut variables. Hooray for less typing!
  $block_id = $vars['block']->module . '-' . $vars['block']->delta;
  $classes = &$vars['classes_array'];
  $title_classes = &$vars['title_attributes_array']['class'];
  $content_classes = &$vars['content_attributes_array']['class'];
  $suggestions = &$vars['theme_hook_suggestions'];

  // Add global classes to all blocks.
  $title_classes[] = 'block-title';
  $content_classes[] = 'block-content';

  // Uncomment the lines below to see variables you can use to target a block.
  // This requires http://drupal.org/project/devel to be installed.
  // dpm($block_id, 'Block ID:');

  switch ($block_id) {
    case 'search-form':
      $classes[] = 'header-search';
      break;
    case 'menu-utility-menu':
      $content_classes[] = 'utility-nav';
      break;
    case 'bean-copyright':
      $classes[] = 'footer-copyright';
      break;
    case 'system-main-menu':
      $content_classes[] = 'nav--main';
      break;
    case 'bean-footer_social':
      $classes[] = 'social--footer';
      break;
    case 'menu-footer-menu':
      $classes[] = 'footer--menu';
      break;
    case 'views-recent_news-block':
      $title_classes[] = 'heading--thin';
      break;
    case 'views-homepage_news-block':
      $title_classes[] = 'heading--section';
      $classes[] = 'l--constrained';
      break;
    case 'views-marquee-marquee_block':
      $content_classes[] = 'l--constrained';
      $classes[] = 'marquee-block';
      $vars['theme_hook_suggestions'][] = 'block__marquee';
      break;
    case 'bean-homepage-home-cta':
      if (isset($vars['bean'])) {
        $wrapper = entity_metadata_wrapper('bean', $vars['bean']);

        $vars['classes_array'][] = 'call-to-action';
        if (!empty($vars['field_main_cta_image'])) {
          $vars['cta_bg'] = image_style_url('large', $wrapper->field_main_cta_image->value()['uri']);
        }
      }

      $vars['block']->subject = '';
      break;
    case 'views-parts-parts_block':
    case 'views-merchandise-merch_block':
    case 'views-tool_heads-th_block':
    case 'views-filament-fila_block':
      $classes[] = 'products--view';
      // dpm($vars);
      break;
    case 'views--exp-parts-parts_block_filters':
    case 'views--exp-tool_heads-th_filters':
    case 'views--exp-filament-fila_filters':
    case 'views--exp-merchandise-merch_block':
    case 'views--exp-parts-parts_block':
    case 'views--exp-filament-fila_block':
    case 'views--exp-tool_heads-th_block':
      $classes[] = 'sidebar-filter';
      $title_classes[] = 'heading--sidebar';
      $vars['theme_hook_suggestions'][] = 'block__sidebar_filter';
      break;
    case 'FILTERS___TOP':
      $classes[] = 'product-filter-top';
      break;
    case 'bean-printers':
      $classes[] = 'printer--comparison';
      break;
    case 'bean-filament':
    case 'bean-tool_heads':
    case 'bean-parts':
    case 'bean-merchandise':
    case 'bean-printers_heading':
      $classes[] = 'store--category';
      $title_classes[] = 'header--store-category';
      break;
  }
}
