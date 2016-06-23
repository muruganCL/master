<?php

class lulzbotMigrateUserUser extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

   parent::__construct($arguments);

   variable_set('password_inc', drupal_get_path('module', 'lulzbot_migrate') . '/password.inc');
    $query = Database::getConnection('default', 'normi')
      ->select('user_user', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationUser();
    $this->description = t('Import user.');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'description' => t('Unique ID'),
          'alias' => 'a',
        ),
      ),
      MigrateDestinationUser::getKeySchema()
    );

    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('mail', 'mail');
    $this->addFieldMapping('init', 'init');

  }

  public function postImport() {
    parent::postImport();
    variable_set('password_inc', 'includes/password.inc');
  }

}
