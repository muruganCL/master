<?php

class lulzbotMigrateNodePart extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_part', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('part');
    $this->description = t('Import part.');

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
    // $this->addFieldMapping('field_part_bg_triangle', 'field_part_bg_triangle');
    // $this->addFieldMapping('field_part_compatible_printers', 'field_part_compatible_printers')->sourceMigration('lulzbotMigrateTaxonomyPartCompatiblePrinters');
    // $this->addFieldMapping('field_part_ease_of_use', 'field_part_ease_of_use')->sourceMigration('lulzbotMigrateTaxonomyEaseOfUse');
    // $this->addFieldMapping('field_part_features', 'field_part_features');
    $this->addFieldMapping('field_part_images', 'field_part_images')->separator(',');
    // $this->addFieldMapping('field_part_learning_links', 'field_part_learning_links')->separator(',');
    // $this->addFieldMapping('field_part_part_types', 'field_part_part_types')->sourceMigration('lulzbotMigrateTaxonomyPartTypes');
    // $this->addFieldMapping('field_part_parts_included', 'field_part_parts_included');
    // $this->addFieldMapping('field_part_project_showcase', 'field_part_project_showcase')->sourceMigration('lulzbotMigrateNodeShowcase')->separator(',');
    // $this->addFieldMapping('field_part_related_products', 'field_part_related_products')->sourceMigration('lulzbotMigrateNodeToolHead')->separator(',');
    // $this->addFieldMapping('field_part_reviews', 'field_part_reviews')->separator(',');
    $this->addFieldMapping('field_part_specifications', 'field_part_specifications');
    $this->addFieldMapping('field_part_specifications:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_product_reference', 'field_product_reference')->separator(',')->sourceMigration('lulzbotMigrateProductPart');
    // $this->addFieldMapping('field_radioactivity', 'field_radioactivity');

  }

}
