<?php

class lulzbotMigrateNodeToolHead extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_tool_head', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('tool_head');
    $this->description = t('Import tool_head.');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'description' => t('Unique ID'),
          'alias' => 'a',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_product_reference', 'field_product_reference')->separator(',')->sourceMigration('lulzbotMigrateProductToolHead');
    // $this->addFieldMapping('field_radioactivity', 'field_radioactivity');
    // $this->addFieldMapping('field_tool_head_bg_triangle', 'field_tool_head_bg_triangle');
    // $this->addFieldMapping('field_tool_head_compatiblity', 'field_tool_head_compatiblity')->sourceMigration('lulzbotMigrateTaxonomyArray')->separator(',');
    // $this->addFieldMapping('field_tool_head_ease_of_use', 'field_tool_head_ease_of_use')->sourceMigration('lulzbotMigrateTaxonomyEaseOfUse');
    // $this->addFieldMapping('field_tool_head_features', 'field_tool_head_features');
    // $this->addFieldMapping('field_tool_head_images', 'field_tool_head_images')->defaultValue('sites/default/files/normi/source')->separator(',');
    // $this->addFieldMapping('field_tool_head_learning_links', 'field_tool_head_learning_links')->separator(',');
    // $this->addFieldMapping('field_tool_head_parts_included', 'field_tool_head_parts_included');
    // $this->addFieldMapping('field_tool_head_project_showcase', 'field_tool_head_project_showcase')->sourceMigration('lulzbotMigrateNodeShowcase')->separator(',');
    // $this->addFieldMapping('field_tool_head_related_products', 'field_tool_head_related_products')->sourceMigration('lulzbotMigrateNodeToolHead')->separator(',');
    // $this->addFieldMapping('field_tool_head_reviews', 'field_tool_head_reviews')->separator(',');
    $this->addFieldMapping('field_tool_head_specifications', 'field_tool_head_specifications');
    $this->addFieldMapping('field_tool_head_specifications:format')->defaultValue('full_html');

  }

}
