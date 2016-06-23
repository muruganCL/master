<?php

class lulzbotMigrateNodeMerchandise extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_merchandise', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('merchandise');
    $this->description = t('Import merchandise.');

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
    // $this->addFieldMapping('field_merchandise_bg_triangle', 'field_merchandise_bg_triangle');
    // $this->addFieldMapping('field_merchandise_images', 'field_merchandise_images')->defaultValue('sites/default/files/normi/source')->separator(',');
    // $this->addFieldMapping('field_merchandise_note_body', 'field_merchandise_note_body');
    // $this->addFieldMapping('field_merchandise_note_title', 'field_merchandise_note_title');
    // $this->addFieldMapping('field_merchandise_related_prods', 'field_merchandise_related_prods')->sourceMigration('lulzbotMigrateNodeMerchandise')->separator(',');
    // $this->addFieldMapping('field_merchandise_reviews', 'field_merchandise_reviews')->separator(',');
    // $this->addFieldMapping('field_product_reference', 'field_product_reference')->separator(',')->sourceMigration('lulzbotMigrateProductTshirt');
    // $this->addFieldMapping('field_radioactivity', 'field_radioactivity');

  }

}
