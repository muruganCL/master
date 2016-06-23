<?php

$view = new view();
$view->name = 'filament';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Filament';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'time';
$handler->display->display_options['cache']['results_lifespan'] = '3600';
$handler->display->display_options['cache']['results_lifespan_custom'] = '0';
$handler->display->display_options['cache']['output_lifespan'] = '3600';
$handler->display->display_options['cache']['output_lifespan_custom'] = '0';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
$handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
$handler->display->display_options['exposed_form']['options']['bef'] = array(
  'general' => array(
    'input_required' => 0,
    'text_input_required' => array(
      'text_input_required' => array(
        'value' => 'Select any filter and click on Apply to see results',
        'format' => 'full_html',
      ),
    ),
    'allow_secondary' => 0,
    'secondary_label' => 'Advanced options',
  ),
  'sort' => array(
    'bef_format' => 'default',
    'advanced' => array(
      'collapsible' => 0,
      'collapsible_label' => 'Sort options',
      'combine' => 1,
      'combine_param' => 'sort_bef_combine',
      'combine_rewrite' => 'Alphabetical Asc|Alphabetical A-Z
Alphabetical Desc|Alphabetical Z-A
Price Asc|Price - Low to High
Price Desc|Price - High to Low
Popularity Desc|Most Popular
Popularity Asc|Least Popular',
      'reset' => 0,
      'reset_label' => '',
      'is_secondary' => 0,
    ),
  ),
  'keys' => array(
    'bef_format' => 'default',
    'more_options' => array(
      'is_secondary' => 0,
      'any_label' => '',
      'bef_filter_description' => '',
      'tokens' => array(
        'available' => array(
          0 => 'global_types',
        ),
      ),
      'rewrite' => array(
        'filter_rewrite_values' => '',
      ),
    ),
  ),
  'field_filament_compatiblity_tid' => array(
    'bef_format' => 'default',
    'more_options' => array(
      'bef_select_all_none' => FALSE,
      'bef_collapsible' => 0,
      'is_secondary' => 0,
      'any_label' => '',
      'bef_filter_description' => '',
      'tokens' => array(
        'available' => array(
          0 => 'global_types',
          1 => 'vocabulary',
        ),
      ),
      'rewrite' => array(
        'filter_rewrite_values' => '',
      ),
    ),
  ),
  'field_filament_weight_tid' => array(
    'bef_format' => 'default',
    'more_options' => array(
      'bef_select_all_none' => FALSE,
      'bef_collapsible' => 0,
      'is_secondary' => 0,
      'any_label' => '',
      'bef_filter_description' => '',
      'tokens' => array(
        'available' => array(
          0 => 'global_types',
          1 => 'vocabulary',
        ),
      ),
      'rewrite' => array(
        'filter_rewrite_values' => '',
      ),
    ),
  ),
  'field_filament_materials_tid' => array(
    'bef_format' => 'default',
    'more_options' => array(
      'bef_select_all_none' => FALSE,
      'bef_collapsible' => 0,
      'is_secondary' => 0,
      'any_label' => '',
      'bef_filter_description' => '',
      'tokens' => array(
        'available' => array(
          0 => 'global_types',
          1 => 'vocabulary',
        ),
      ),
      'rewrite' => array(
        'filter_rewrite_values' => '',
      ),
    ),
  ),
  'field_filament_applications_tid' => array(
    'bef_format' => 'bef',
    'more_options' => array(
      'bef_select_all_none' => 0,
      'bef_collapsible' => 0,
      'is_secondary' => 0,
      'any_label' => '',
      'bef_filter_description' => '',
      'tokens' => array(
        'available' => array(
          0 => 'global_types',
          1 => 'vocabulary',
        ),
      ),
      'rewrite' => array(
        'filter_rewrite_values' => '',
      ),
    ),
  ),
);
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '100';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'No results text';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'There is no filament matching your search criteria.';
$handler->display->display_options['empty']['area']['format'] = 'full_html';
/* Relationship: Content: Referenced products */
$handler->display->display_options['relationships']['field_product_reference_product_id']['id'] = 'field_product_reference_product_id';
$handler->display->display_options['relationships']['field_product_reference_product_id']['table'] = 'field_data_field_product_reference';
$handler->display->display_options['relationships']['field_product_reference_product_id']['field'] = 'field_product_reference_product_id';
$handler->display->display_options['relationships']['field_product_reference_product_id']['label'] = 'Products referenced';
$handler->display->display_options['relationships']['field_product_reference_product_id']['required'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['exclude'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
/* Field: Content: Rendered Node */
$handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
$handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
$handler->display->display_options['fields']['rendered_entity']['label'] = '';
$handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
$handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
$handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'teaser';
$handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
/* Field: Content: Body */
$handler->display->display_options['fields']['body']['id'] = 'body';
$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
$handler->display->display_options['fields']['body']['field'] = 'body';
$handler->display->display_options['fields']['body']['label'] = '';
$handler->display->display_options['fields']['body']['exclude'] = TRUE;
$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['body']['type'] = 'text_plain';
/* Sort criterion: Content: Title */
$handler->display->display_options['sorts']['title']['id'] = 'title';
$handler->display->display_options['sorts']['title']['table'] = 'node';
$handler->display->display_options['sorts']['title']['field'] = 'title';
$handler->display->display_options['sorts']['title']['exposed'] = TRUE;
$handler->display->display_options['sorts']['title']['expose']['label'] = 'Alphabetical';
/* Sort criterion: Content: Popularity (field_radioactivity:radioactivity_energy) */
$handler->display->display_options['sorts']['field_radioactivity_radioactivity_energy']['id'] = 'field_radioactivity_radioactivity_energy';
$handler->display->display_options['sorts']['field_radioactivity_radioactivity_energy']['table'] = 'field_data_field_radioactivity';
$handler->display->display_options['sorts']['field_radioactivity_radioactivity_energy']['field'] = 'field_radioactivity_radioactivity_energy';
$handler->display->display_options['sorts']['field_radioactivity_radioactivity_energy']['exposed'] = TRUE;
$handler->display->display_options['sorts']['field_radioactivity_radioactivity_energy']['expose']['label'] = 'Popularity';
/* Sort criterion: Commerce Product: Price (commerce_price:amount) */
$handler->display->display_options['sorts']['commerce_price_amount']['id'] = 'commerce_price_amount';
$handler->display->display_options['sorts']['commerce_price_amount']['table'] = 'field_data_commerce_price';
$handler->display->display_options['sorts']['commerce_price_amount']['field'] = 'commerce_price_amount';
$handler->display->display_options['sorts']['commerce_price_amount']['relationship'] = 'field_product_reference_product_id';
$handler->display->display_options['sorts']['commerce_price_amount']['exposed'] = TRUE;
$handler->display->display_options['sorts']['commerce_price_amount']['expose']['label'] = 'Price';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'filament' => 'filament',
);
$handler->display->display_options['filters']['type']['group'] = 1;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
  10 => 0,
  11 => 0,
  12 => 0,
  13 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'title' => 'title',
  'body' => 'body',
);
/* Filter criterion: Content: Compatible Printers/Tool Heads (field_filament_compatiblity) */
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['id'] = 'field_filament_compatiblity_tid';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['table'] = 'field_data_field_filament_compatiblity';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['field'] = 'field_filament_compatiblity_tid';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['group'] = 1;
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['expose']['operator_id'] = 'field_filament_compatiblity_tid_op';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['expose']['label'] = 'Printer/Tool Head';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['expose']['operator'] = 'field_filament_compatiblity_tid_op';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['expose']['identifier'] = 'field_filament_compatiblity_tid';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
  10 => 0,
  11 => 0,
  12 => 0,
  13 => 0,
);
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_filament_compatiblity_tid']['vocabulary'] = 'filament_compatible';
/* Filter criterion: Content: Weight (field_filament_weight) */
$handler->display->display_options['filters']['field_filament_weight_tid']['id'] = 'field_filament_weight_tid';
$handler->display->display_options['filters']['field_filament_weight_tid']['table'] = 'field_data_field_filament_weight';
$handler->display->display_options['filters']['field_filament_weight_tid']['field'] = 'field_filament_weight_tid';
$handler->display->display_options['filters']['field_filament_weight_tid']['group'] = 1;
$handler->display->display_options['filters']['field_filament_weight_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_filament_weight_tid']['expose']['operator_id'] = 'field_filament_weight_tid_op';
$handler->display->display_options['filters']['field_filament_weight_tid']['expose']['label'] = 'Weight';
$handler->display->display_options['filters']['field_filament_weight_tid']['expose']['operator'] = 'field_filament_weight_tid_op';
$handler->display->display_options['filters']['field_filament_weight_tid']['expose']['identifier'] = 'field_filament_weight_tid';
$handler->display->display_options['filters']['field_filament_weight_tid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
  10 => 0,
  11 => 0,
  12 => 0,
  13 => 0,
);
$handler->display->display_options['filters']['field_filament_weight_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_filament_weight_tid']['vocabulary'] = 'weight';
/* Filter criterion: Content: Material(s) (field_filament_materials) */
$handler->display->display_options['filters']['field_filament_materials_tid']['id'] = 'field_filament_materials_tid';
$handler->display->display_options['filters']['field_filament_materials_tid']['table'] = 'field_data_field_filament_materials';
$handler->display->display_options['filters']['field_filament_materials_tid']['field'] = 'field_filament_materials_tid';
$handler->display->display_options['filters']['field_filament_materials_tid']['group'] = 1;
$handler->display->display_options['filters']['field_filament_materials_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_filament_materials_tid']['expose']['operator_id'] = 'field_filament_materials_tid_op';
$handler->display->display_options['filters']['field_filament_materials_tid']['expose']['label'] = 'Material Type';
$handler->display->display_options['filters']['field_filament_materials_tid']['expose']['operator'] = 'field_filament_materials_tid_op';
$handler->display->display_options['filters']['field_filament_materials_tid']['expose']['identifier'] = 'field_filament_materials_tid';
$handler->display->display_options['filters']['field_filament_materials_tid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
  10 => 0,
  11 => 0,
  12 => 0,
  13 => 0,
);
$handler->display->display_options['filters']['field_filament_materials_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_filament_materials_tid']['vocabulary'] = 'materials';
/* Filter criterion: Content: Ideal Application(s) (field_filament_applications) */
$handler->display->display_options['filters']['field_filament_applications_tid']['id'] = 'field_filament_applications_tid';
$handler->display->display_options['filters']['field_filament_applications_tid']['table'] = 'field_data_field_filament_applications';
$handler->display->display_options['filters']['field_filament_applications_tid']['field'] = 'field_filament_applications_tid';
$handler->display->display_options['filters']['field_filament_applications_tid']['group'] = 1;
$handler->display->display_options['filters']['field_filament_applications_tid']['operator'] = 'and';
$handler->display->display_options['filters']['field_filament_applications_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['operator_id'] = 'field_filament_applications_tid_op';
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['label'] = 'Ideal Application';
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['operator'] = 'field_filament_applications_tid_op';
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['identifier'] = 'field_filament_applications_tid';
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['field_filament_applications_tid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
  10 => 0,
  11 => 0,
  12 => 0,
  13 => 0,
);
$handler->display->display_options['filters']['field_filament_applications_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_filament_applications_tid']['vocabulary'] = 'ideal_applications';

/* Display: Block */
$handler = $view->new_display('block', 'Block', 'fila_block');
$handler->display->display_options['exposed_block'] = TRUE;

/* Display: Block */
$handler = $view->new_display('block', 'Block', 'fila_filters');
$handler->display->display_options['enabled'] = FALSE;
$handler->display->display_options['exposed_block'] = TRUE;
