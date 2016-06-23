<?php

/**
 * Implements hook_preprocess_node()
 */
function lulzbot_preprocess_node(&$vars) {

  // Set shortcut variables. Hooray for less typing!
  $type = $vars['type'];
  $mode = $vars['view_mode'];
  $classes = &$vars['classes_array'];
  $title_classes = &$vars['title_attributes_array']['class'];
  $content_classes = &$vars['content_attributes_array']['class'];
  global $language;

  // Uncomment the lines below to see variables you can use to target a field.
  // This requires http://drupal.org/project/devel to be installed.
  // dpm($type, 'Type:');
  // dpm($mode, 'Mode:');

  if ($mode === 'feature') {
    $classes[] = 'feature';
  }

  if ($mode === 'compare') {
    $classes[] = 'compare';
    $title_classes[] = 'compare--printer-title';
  }

  if ($mode === 'promo') {
    $classes[] = 'promo';
    // Set type
    $content_type = array(
      'in_the_news' => 'In The News',
      'forum-post' => 'Forum',
      'event' => 'Event',
      'announcement' => 'Announcement',
      'case_study' => 'Case Study',
      'tutorial' => 'Tutorial',
    );

    foreach ($content_type as $key => $value) {
      if ($key === $vars['type']) {
        $vars['content']['promo_type'] = array('#markup' => $value);
        $vars['content']['promo_type_slideout'] = array('#markup' => $value);
      }

      if (!empty($vars['field_' . $key . '_image'])) {
        $promo_uri = $vars['field_' . $key . '_image'][0]['uri'];
        $promo_path = image_style_url('large', $promo_uri);

        $vars['promo_background'] = $promo_path;
      }
    }

    // Add ellipses
    if (isset($vars['content']['body'][0]['#markup'])) {
      foreach ($vars['content']['body'] as $key => $value) {
        if (is_integer($key)) {
          $body_elips = strip_tags(_limit_words(strip_tags($value['#markup'], '<a>'), 22), '<a>');
          $elips = '...';
          if (strlen($body_elips) <= 15) {
            $elips = '';
          }
          // dpm(strip_tags($value['#markup'], '<a>'));
          $vars['content']['body'][$key]['#markup'] = $body_elips . $elips;
        }
      }
    }

    $title_classes[] = 'promo-title';

    // Dupe title
    $vars['content']['title_slideout'] = array('#markup' => $vars['title']);
  }

  if ($mode === 'teaser' && in_array($type, ['part', 'merchandise', 'filament', 'tool_head'])) {
    $vars['theme_hook_suggestions'][] = 'node__product__teaser';
    $title_classes[] = 'product-teaser--title';
    $title_classes[] = 'heading--link-text';
  }

  $wrapper = entity_metadata_wrapper('node', $vars['node']);
  switch ($type) {
    case 'printer':
    case 'merchandise':
    case 'part':
    case 'tool_head':
    case 'filament':
      if ($mode === 'full') {
        $title_classes[] = 'product--title';

        // Filament width/weight
        if (isset($vars['content']['field_filament_weight']) || isset($vars['content']['field_filament_width'])) {
          $title_classes[] = 'product--title-width-weight';
        }

        $product_img_fields = array(
          'field_merchandise_images',
          'field_part_images',
          'field_tool_head_images',
          'field_filament_images',
        );

        foreach ($product_img_fields as $key => $value) {
          if (!empty($vars[$value]) ) {

            $last_images = $vars['content'][$value];

            $vars['content']['first_product_image'] = $last_images[0];
          }
        }

        if (!empty($vars['field_printer_images']) ) {

          $last_images = $vars['content']['field_printer_images'];
          unset($last_images[0]);

          $vars['content']['field_printer_images_thumbnails'] = $last_images;

          foreach ($vars['content']['field_printer_images'] as $key => $value) {
            if (is_int($key) && $key !== 0) {
              unset($vars['content']['field_printer_images'][$key]);
            }
          }
        }

        // Alert counts
        $alert_field = array(
          'field_merchandise_alerts',
          'field_part_alerts',
          'field_printer_alerts',
          'field_tool_head_alerts',
          'field_filament_alerts',
        );

        foreach ($alert_field as $value) {
          if (isset($vars[$value]) ) {
            $alert_count = count($vars[$value]);
            $vars['content']['alert_count'] = array('#markup' => $alert_count);
          }
        }


        if (!empty($vars['field_printer_fc1_image'])) {
          $vars['feature1_classes'] = 'feature--bg';
          $vars['feature1_background'] = file_create_url($wrapper->field_printer_fc1_image->value()['uri']);

        }
        if (!empty($vars['field_printer_fc3_bg_image'])) {
          $vars['feature3_classes'] = 'feature--bg';
          $vars['feature3_background'] = file_create_url($wrapper->field_printer_fc3_bg_image->value()['uri']);
        }

        $content_types = array(
          'merchandise',
          'part',
          'th',
          'filament',
        );

        foreach ($content_types as $type) {
          if (!empty($vars['field_' . $type . '_video_bg_image'])) {
            $vars['video_classes'] = 'feature--bg';
            $vars['video_background'] = file_create_url($wrapper->{'field_' . $type . '_video_bg_image'}->value()['uri']);
          } else {
            $vars['video_classes'] = 'feature--bg';
            $vars['video_background'] = '/' . drupal_get_path('theme', 'lulzbot') . '/src/img/printer_printing.png';
          }
        }

        // add product images to node image
        if (!empty($vars['field_product_reference']) && $vars['type'] === 'filament') {
          foreach ($wrapper->field_product_reference->value() as $key => $value) {
            $product = entity_metadata_wrapper('commerce_product', $value);
            if (!empty($product->field_product_filament_image->value())) {
              $product_image = $product->field_product_filament_image->value()[0];
              $vars['node']->field_filament_images['und'][] = $product_image;
            }
          }
          $vars['content']['field_filament_images'] = field_view_field('node', $vars['node'], 'field_filament_images', 'full');
        }

        if (!empty($vars['field_printer_reviews'])) {

          $wrapper = entity_metadata_wrapper('node', $vars['node']);

          $field_collections = array();
          foreach ($wrapper->field_printer_reviews as $i => $fc) {
            $image_uri = $fc->field_review_image->value()['uri'];
            $image_settings = array(
              'style_name' => 'review_tiny',
              'path' => $image_uri,
              'width' => '',
              'height' => '',
            );
            if ($image_uri !== null || $i > 2) {
              array_push($field_collections, theme_image_style($image_settings));
            }
          }

          $vars['review_images_tiny'] = $field_collections;
        }

        // Support links
        $support_links = '';
        foreach (lulzbot_products_get_support_links_for_product($vars['node'], array('attributes' => array('class' => array('link--go', 'link--text', 'link--small', 'link--block')))) as $key => $value) {
           $support_links .= $value;
        }

        $vars['support_links'] = $support_links;
      }

      if ($mode === 'feature') {
        $title_classes[] = 'heading--bold';
        $title_classes[] = 'heading--link-text';
      }

      break;
    case 'article':
    case 'in_the_news':
    case 'announcement':
    case 'forum_post':
    case 'event':
    case 'case_study':
    case 'tutorial':

      if ($mode === 'simple') {
        $title_classes[] = 'heading--bold';
      }

      // Teaser
      if ($vars['view_mode'] === 'teaser') {
        // Product fields
        $wrapper = entity_metadata_wrapper('node', $vars['node']);

        $field = 'field_forum_image';

        // Product type
        $vars['product_type'] = ucwords(str_replace('_', ' ', $wrapper->getBundle()));

        // classes
        $title_classes[] = 'heading--small';
        $title_classes[] = 'heading--link-text';
        $classes[] = 'clearfix';
        $classes[] = 'support--teaser';
      }

      // Article date
      $vars['created'] = format_date($vars['node']->created, 'lulzbot_full');

      break;
    case 'page':
      unset($vars['content']['field_page_image']);
      unset($vars['content']['field_page_intro']);
      break;
    case 'support':
      _lulzbot_support_node($vars);
      break;
  }

  $preprocesses = array(
    $mode,
    $type,
    $type . '__' . $mode,
  );
  center_preprocessors($vars, __FUNCTION__, $preprocesses);
}


/**
 * Word limiter
 *
 * @param      string  $string      string to be truncated
 * @param      int  $word_limit  amount of words to return
 *
 * @return     string
 */
function _limit_words($string, $word_limit) {
  $words = explode(' ' ,$string);
  return implode(' ',array_splice($words,0,$word_limit));
}

/**
 * Settings for support nodes
 *
 * @param $vars   node variables
 */
function _lulzbot_support_node(&$vars) {
  $title_classes = &$vars['title_attributes_array']['class'];
  $classes = &$vars['classes_array'];

  // Teaser
  if ($vars['view_mode'] === 'teaser') {
    // Product fields
    $wrapper = entity_metadata_wrapper('node', $vars['node']);
    $product = $wrapper->field_support_product->value();
    $field = 'field_' . $product->type . '_images';
    if (stools_field_has_value($product, $field)) {
      $vars['image'] = theme('image_style', array('path' => $product->{$field}[LANGUAGE_NONE][0]['uri'], 'style_name' => 'medium'));
    }
    if (stools_field_has_value($product, 'body')) {
      $vars['description'] = _limit_words(strip_tags($product->body[LANGUAGE_NONE][0]['safe_value']), 25) . '...';
    }

    // Product type
    $vars['product_type'] = ucwords(str_replace('_', ' ', $product->type));

    // classes
    $title_classes[] = 'heading--small';
    $title_classes[] = 'heading--link-text';
    $classes[] = 'clearfix';
    $classes[] = 'support--teaser';
  }

  // Full
  if ($vars['view_mode'] === 'full') {
    $title_classes[] = 'product--title';

    $noder = node_load($vars['node']->field_support_product[LANGUAGE_NONE][0]['target_id']);
    $node_view = node_view($noder, 'full');

    $content_types = array(
      'merchandise',
      'part',
      'tool_head',
      'filament',
      'printer'
    );

    foreach ($node_view as $key => $item) {
      foreach ($content_types as $i => $type) {
        if (strpos($key, '_'.$type.'_') !== false) {
          $node_view[str_replace('_'.$type, '', $key)] = $item;
          unset($node_view[$key]);
        }
      }
    }

    $vars['product_ref'] = $node_view;
  }
}
