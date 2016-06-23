<?php

class lulzbotMigrateProductPrinter extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('product_printer', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationCommerceProduct('commerce_product', 'printer');
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
      MigrateDestinationCommerceProduct::getKeySchema('commerce_product', 'printer')
    );

    $this->addFieldMapping('id', 'id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('type', 'type');
    $this->addFieldMapping('commerce_price', 'commerce_price');

  }

}
