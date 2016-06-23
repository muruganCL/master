<?php

class lulzbotMigrateProductTshirt extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('product_tshirt', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationCommerceProduct('commerce_product', 'tshirt');
    $this->description = t('Import tshirt.');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'description' => t('Unique ID'),
          'alias' => 'a',
        ),
      ),
      MigrateDestinationCommerceProduct::getKeySchema('commerce_product', 'tshirt')
    );

    $this->addFieldMapping('id', 'id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('type', 'type');
    // $this->addFieldMapping('commerce_price', 'commerce_price');
    // $this->addFieldMapping('field_product_tshirt_colors', 'field_product_tshirt_colors')->sourceMigration('lulzbotMigrateTaxonomyTshirtColors');
    // $this->addFieldMapping('field_product_tshirt_sizes', 'field_product_tshirt_sizes')->sourceMigration('lulzbotMigrateTaxonomyTshirtSizes');
    // $this->addFieldMapping('field_product_tshirt_type', 'field_product_tshirt_type');

  }

  public function prepare($entity, $row) {
  }

}
