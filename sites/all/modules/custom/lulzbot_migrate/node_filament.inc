<?php

class lulzbotMigrateNodeFilament extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_filament', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('filament');
    $this->description = t('Import filament.');

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
    // $this->addFieldMapping('field_filament_applications', 'field_filament_applications')->sourceMigration('lulzbotMigrateTaxonomyIdealApplications')->separator(',');
    // $this->addFieldMapping('field_filament_bg_triangle', 'field_filament_bg_triangle');
    // $this->addFieldMapping('field_filament_compatiblity', 'field_filament_compatiblity')->sourceMigration('lulzbotMigrateTaxonomyFilamentCompatible')->separator(',');
    // $this->addFieldMapping('field_filament_ease_of_use', 'field_filament_ease_of_use')->sourceMigration('lulzbotMigrateTaxonomyEaseOfUse');
    // $this->addFieldMapping('field_filament_features', 'field_filament_features');
    // $this->addFieldMapping('field_filament_materials', 'field_filament_materials')->sourceMigration('lulzbotMigrateTaxonomyMaterials')->separator(',');
    // $this->addFieldMapping('field_filament_project_showcase', 'field_filament_project_showcase')->sourceMigration('lulzbotMigrateNodeShowcase')->separator(',');
    // $this->addFieldMapping('field_filament_related_filaments', 'field_filament_related_filaments')->sourceMigration('lulzbotMigrateNodeFilament')->separator(',');
    $this->addFieldMapping('field_filament_specifications', 'field_filament_specifications');
    $this->addFieldMapping('field_filament_specifications:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_filament_supplier', 'field_filament_supplier');
    // $this->addFieldMapping('field_filament_weight', 'field_filament_weight')->sourceMigration('lulzbotMigrateTaxonomyWeight');
    // $this->addFieldMapping('field_filament_width', 'field_filament_width')->sourceMigration('lulzbotMigrateTaxonomyWidth');
    // $this->addFieldMapping('field_product_reference', 'field_product_reference')->separator(',')->sourceMigration('lulzbotMigrateProductFilament');
    // $this->addFieldMapping('field_radioactivity', 'field_radioactivity');
    // $this->addFieldMapping('field_tool_head_learning_links', 'field_tool_head_learning_links')->separator(',');

  }

}
