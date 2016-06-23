<?php

class lulzbotMigrateProductFilament extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('product_filament', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationCommerceProduct('commerce_product', 'filament');
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
      MigrateDestinationCommerceProduct::getKeySchema('commerce_product', 'filament')
    );

    $this->addFieldMapping('id', 'id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('type', 'type');
    $this->addFieldMapping('commerce_price', 'commerce_price');
    // $this->addFieldMapping('field_product_filament_colors', 'field_product_filament_colors')->sourceMigration('lulzbotMigrateTaxonomyFilamentColors');

  }

}
