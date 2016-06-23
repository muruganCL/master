<?php

class lulzbotMigrateNodePage extends Migration {

  /**
   * Constructor
   */
 public function __construct($arguments) {

   parent::__construct($arguments);
   
    $query = Database::getConnection('default', 'normi')
      ->select('node_page', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('page');
    $this->description = t('Import page.');

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

    $this->addFieldMapping('uid', 'uid')->defaultValue(0); // ->sourceMigration('lulzbotMigrateUserUser');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_page_file', 'field_page_file')->defaultValue('sites/default/files/normi/source');
    // $this->addFieldMapping('field_part_bg_triangle', 'field_part_bg_triangle');

  }

}
