<?php

class lulzbotMigrateNodePrinter extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_printer', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('printer');
    $this->description = t('Import printer.');

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
    // $this->addFieldMapping('field_printer_bg_triangle', 'field_printer_bg_triangle');
    // $this->addFieldMapping('field_printer_ease_of_use', 'field_printer_ease_of_use')->sourceMigration('lulzbotMigrateTaxonomyEaseOfUse');
    // $this->addFieldMapping('field_printer_fc1_description', 'field_printer_fc1_description');
    // $this->addFieldMapping('field_printer_fc1_image', 'field_printer_fc1_image')->defaultValue('sites/default/files/normi/source');
    // $this->addFieldMapping('field_printer_fc1_link', 'field_printer_fc1_link');
    // $this->addFieldMapping('field_printer_fc1_text', 'field_printer_fc1_text');
    // $this->addFieldMapping('field_printer_fc2_description', 'field_printer_fc2_description');
    // $this->addFieldMapping('field_printer_fc2_image', 'field_printer_fc2_image')->defaultValue('sites/default/files/normi/source');
    // $this->addFieldMapping('field_printer_fc2_link', 'field_printer_fc2_link');
    // $this->addFieldMapping('field_printer_fc2_products', 'field_printer_fc2_products')->sourceMigration('lulzbotMigrateNodeFilament')->separator(',');
    // $this->addFieldMapping('field_printer_fc2_rel_title', 'field_printer_fc2_rel_title');
    // $this->addFieldMapping('field_printer_fc2_text', 'field_printer_fc2_text');
    // $this->addFieldMapping('field_printer_fc3_bg_image', 'field_printer_fc3_bg_image')->defaultValue('sites/default/files/normi/source');
    // $this->addFieldMapping('field_printer_fc3_description', 'field_printer_fc3_description');
    // $this->addFieldMapping('field_printer_fc3_image', 'field_printer_fc3_image')->defaultValue('sites/default/files/normi/source');
    // $this->addFieldMapping('field_printer_fc3_link', 'field_printer_fc3_link')->separator(',');
    // $this->addFieldMapping('field_printer_fc3_text', 'field_printer_fc3_text');
    // $this->addFieldMapping('field_printer_fc3_video', 'field_printer_fc3_video');
    $this->addFieldMapping('field_printer_images', 'field_printer_images')->separator(',');
    $this->addFieldMapping('field_printer_parts_specs1', 'field_printer_parts_specs1');
    $this->addFieldMapping('field_printer_parts_specs1:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_printer_parts_specs2', 'field_printer_parts_specs2');
    // $this->addFieldMapping('field_printer_parts_specs3', 'field_printer_parts_specs3');
    // $this->addFieldMapping('field_printer_reviews', 'field_printer_reviews')->separator(',');
    // $this->addFieldMapping('field_product_reference', 'field_product_reference')->separator(',')->sourceMigration('lulzbotMigrateProductPrinter');
    // $this->addFieldMapping('field_radioactivity', 'field_radioactivity');

  }

}
