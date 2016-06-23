<?php

class lulzbotMigrateNodeAnnouncement extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('node_announcement', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('announcement');
    $this->description = t('Import announcement.');

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
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    // $this->addFieldMapping('field_announcement_bg_triangle', 'field_announcement_bg_triangle');
    // $this->addFieldMapping('field_announcement_topics', 'field_announcement_topics')->sourceMigration('lulzbotMigrateTaxonomyTopics');
    // $this->addFieldMapping('field_announcement_weight', 'field_announcement_weight');

  }

}
