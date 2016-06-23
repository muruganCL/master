<?php

/**
 * Implements hook_preprocess_page()
 */
function lulzbot_preprocess_page(&$vars) {
  $preprocesses = array('user');
  $classes = &$vars['classes_array'];
  $title_classes = &$vars['title_attributes_array']['class'];
  $status = drupal_get_http_header("status");

  // Set default page title behavior.
  $vars['show_title'] = TRUE;

  // Get the svg + png logo paths.
  _lulzbot_add_logo($vars);

  // Display number of cart items
  _lulzbot_number_in_cart($vars);

  // Global
  $vars['copyright'] = stools_render_block('bean', 'copyright');
  if (isset($vars['page']['footer']['bean_footer_social'])) {
    $vars['page']['footer']['bean_footer_social_drawer'] = $vars['page']['footer']['bean_footer_social'];
  }

  // Preprocess node pages by type.
  if (isset($vars['node'])) {
    $preprocesses[] = $vars['node']->type;
    $node_type = $vars['node']->type;
    $vars['theme_hook_suggestions'][] = 'page__' . $node_type;

    switch ($node_type) {
      case 'printer':
      case 'part':
      case 'merchandise':
      case 'tool_head':
      case 'filament':
      case 'support':
        $vars['show_title'] = FALSE;
        $vars['theme_hook_suggestions'][] = 'page__full_bleed';
        break;
      case 'article':
      case 'in_the_news':
      case 'announcement':
      case 'forum_post':
      case 'event':
      case 'case_study':
      case 'tutorial':
        $classes[] = 'image-callout';

        $vars['theme_hook_suggestions'][] = 'page__full_image_callout';

        $wrapper = entity_metadata_wrapper('node', $vars['node']);

        if ($wrapper->__isset('field_event_feature_image') && isset($wrapper->field_event_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_event_feature_image->value()['uri']);
        }
        if ($wrapper->__isset('field_in_the_news_feature_image') && isset($wrapper->field_in_the_news_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_in_the_news_feature_image->value()['uri']);
        }
        if ($wrapper->__isset('field_forum_feature_image') && isset($wrapper->field_forum_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_forum_feature_image->value()['uri']);
        }
        if ($wrapper->__isset('field_case_study_feature_image') && isset($wrapper->field_case_study_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_case_study_feature_image->value()['uri']);
        }
        if ($wrapper->__isset('field_announcement_feature_image') && isset($wrapper->field_announcement_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_announcement_feature_image->value()['uri']);
        }
        if ($wrapper->__isset('field_tutorial_feature_image') && isset($wrapper->field_tutorial_feature_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_tutorial_feature_image->value()['uri']);
        }

        // Article date
        $vars['created'] = format_date($vars['node']->created, 'lulzbot_full');

        break;
      case 'page':
        $title_classes[] = 'basic-page--title';

        $wrapper = entity_metadata_wrapper('node', $vars['node']);

        if ($wrapper->__isset('field_page_image') && isset($wrapper->field_page_image->value()['uri'])) {
          $classes[] = 'image-visible';
          $vars['callout_image'] = file_create_url($wrapper->field_page_image->value()['uri']);
        }
        if ($wrapper->__isset('field_page_intro')) {
          $vars['intro'] = $wrapper->field_page_intro->value()['safe_value'];
        }

        // Support page - sidebar needs to at top on mobile
        if (isset($vars['page']['content']['views_support-support_block'])) {
          $vars['theme_hook_suggestions'][] = 'page__page_sidebar_first';
          $classes[] = 'sidebar-before-content';
        }

        break;
    }
  }

  $templates = array(
    'page__store__parts',
    'page__store__merchandise',
    'page__store__filament',
    'page__store__tool_heads',
    'page__store',
  );

  if (!empty(array_intersect($templates, $vars['theme_hook_suggestions']))) {
    $title_classes[] = 'basic-page--title';
    $vars['theme_hook_suggestions'][] = 'page__page';
    $vars['callout_image'] = '/sites/all/themes/lulzbot/src/img/filament_large_bg.png';
    $vars['page']['content']['bean_printers']['bean']['printers']['#view_mode'] = 'teaser';

    _lulzbot_feature_image($vars);

    $compare_keys = array(
      'views_-exp-parts-parts_block',
      'views_-exp-tool_heads-th_block',
      'views_-exp-filament-fila_block',
      'views_-exp-merchandise-merch_block',
    );

    if (!empty(array_intersect($compare_keys, $vars['page']['content']))) {
      $classes[] = 'no-sidebar-filters';
    }
  }

  // Search page
  if (in_array('page__search', $vars['theme_hook_suggestions'])) {
    drupal_set_title('Search');
  }

  // Homepage
  if (drupal_is_front_page()) {
    $vars['theme_hook_suggestions'][] = 'page__full_bleed';
  }

  // Custom 403 Forbidden Page
  if($status == '403 Forbidden') {
    //$vars['template_files'][] = "page-403";
    $vars['theme_hook_suggestions'][] = 'page__403';
  }

  center_preprocessors($vars, __FUNCTION__, $preprocesses);
}

/**
 * Page preprocess.
 */
function lulzbot_preprocess_page__user(&$vars) {
  // display the user profile field field_user_companies if the user has a value
  $vars['has_company'] = (isset($vars['page']['content']['system_main']) && stools_content_has_value($vars['page']['content']['system_main'], 'field_user_companies'));
  if ($vars['has_company']) {
    $vars['user_company'] = array();
    foreach ($vars['page']['content']['system_main']['field_user_companies'] as $key => $value) {
      if (is_numeric($key)) {
        $vars['user_company'][] = $value['#markup'];
      }
    }

    $label = format_plural(count($vars['user_company']), t('Verified Company'), t('Verified Companies'));
    $vars['user_company_label'] = $label;
    $vars['user_company_value'] = implode(', ', $vars['user_company']);
  }
  unset($vars['page']['content']['system_main']['field_user_companies']);
}

/**
 * Implements hook_page_alter()
 */
function lulzbot_page_alter(&$page) {
  $preprocesses = array();

  $args = arg();
  $args_count = count($args);
  if ($args_count === 4 && $args[0] === 'user' && is_numeric($args[1]) && $args[2] === 'orders' && is_numeric($args[3])) {
    if (module_exists('lulzbot_store')) {
      module_load_include('inc', 'lulzbot_store', 'includes/lulzbot_store.pages');
      lulzbot_store_order_page_alter($page);
    }
  }

  _lulzbot_add_grunticon_support($page);
}

/**
 * Overrides the feature image if page description bean has an image set
 *
 * @param      &     $vars   page variables
 */
function _lulzbot_feature_image(&$vars) {
  $beans = array(
    'tool_heads_intro_text',
    'parts_intro_text',
    'merchandise_intro_text',
    'filament_intro_text',
    'store_intro_text'
  );

  if (!empty($vars['page']['above_content'])) {
    foreach ($vars['page']['above_content'] as $key => $value) {
      $mod_key = str_replace('bean_', '', $key);
      if (in_array($mod_key, $beans)) {
        $bean = bean_load_delta($mod_key);
        if ($bean && isset($bean->field_bean_general_image[LANGUAGE_NONE][0]['uri'])) {
          $vars['callout_image'] = file_create_url($bean->field_bean_general_image[LANGUAGE_NONE][0]['uri']);
        }
      }
    }
  }
}

/**
 * Add Grunticon stylesheet loader.
 */
function _lulzbot_add_grunticon_support(&$page) {
  /**
   * Array of stylesheets.
   *  This is the default, if you set custom stylesheet names in
   *  Gruntfile.js, update these to reflect those changes.
   */
  $grunticon_stylesheets = array(
    'svg' => 'icons.data.svg.css',
    'png' =>  'icons.data.png.css',
    'fallback' =>  'icons.fallback.css',
  );

  /**
   * Add the absolute path to your stylesheets.
   *  This will depend on your Grunticon task's 'dest' option.
   *  Update this path accordingly.
   */
  array_walk($grunticon_stylesheets, function (&$value, $key) {
    $value = '"' . $GLOBALS['base_url'] . '/' . $GLOBALS['theme_path'] . '/build/img/svg/' . $value . '"';
    }
  );

  $page['content']['#attached']['js'][] = array(
    'data' => path_to_theme() . '/build/img/svg/grunticon.loader.js',
    'scope' => 'footer',
    'type' => 'file',
    'weight' => -2
  );

  $page['content']['#attached']['js'][] = array(
    'data' => 'grunticon([' . implode(', ', $grunticon_stylesheets) . ']);',
    'type' => 'inline',
    'scope' => 'footer',
    'weight' => -1
  );

  /**
   * Inject the noscript fallback snippet.
   */
  $grunticon_fallback = array(
    '#type' => 'markup',
    '#markup' => '<noscript><link href=' . $grunticon_stylesheets["fallback"] . ' rel="stylesheet"></noscript>',
  );
  drupal_add_html_head($grunticon_fallback, 'grunticon_fallback');
}

/**
 * Adds the paths to the svg and png versions of the logo.
 */
function _lulzbot_add_logo(&$vars) {
  $vars['logo_svg'] = '/' . path_to_theme() . '/src/img/svg/logo.svg';
  $vars['logo_png'] = '/' . path_to_theme() . '/build/img/svg/png/logo.png';
  $vars['logo_small_svg'] = '/' . path_to_theme() . '/src/img/svg/logo-small.svg';
  $vars['logo_small_png'] = '/' . path_to_theme() . '/build/img/svg/png/logo-small.png';
}

/**
 * Adds number of items in cart to menu button
 */
function _lulzbot_number_in_cart(&$vars) {
  global $user;

  $quantity = 0;
  $order = commerce_cart_order_load($user->uid);
  if ($order) {
      $wrapper = entity_metadata_wrapper('commerce_order', $order);
      $line_items = $wrapper->commerce_line_items;
      $quantity = commerce_line_items_quantity($line_items, commerce_product_line_item_types());
      $total = commerce_line_items_total($line_items);
      $currency = commerce_currency_load($total['currency_code']);
  }
  $vars['cart_items_num'] = format_plural($quantity, '1', '@count');
}
