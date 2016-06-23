<?php

class lulzbotMigrateProductPart extends Migration {

  /**
   * Constructor
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $query = Database::getConnection('default', 'normi')
      ->select('product_part', 'a')
      ->fields('a');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationCommerceProduct('commerce_product', 'part');
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
      MigrateDestinationCommerceProduct::getKeySchema('commerce_product', 'part')
    );

    $this->addFieldMapping('id', 'id');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('type', 'type');
    $this->addFieldMapping('commerce_price', 'commerce_price');

  }

}
