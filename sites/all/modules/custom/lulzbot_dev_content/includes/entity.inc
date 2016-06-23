<?php
module_load_include('inc', 'lulzbot_dev_content', 'lulzbot_dev_content.content');

/**
 * Manage entity items.
 */
class DevContentEntityItem extends DevContentItem {
  public $entityType;
  public $bundle;
  public $assets = array();

  /**
   * Constructor
   */
  public function __construct($file, $data, $file_data) {
    parent::__construct($file, $data, $file_data);
    $this->entityType = $file_data['entity_type'];
    $this->bundle = $file_data['bundle'];

    // check that our entity/bundle exist
    $info = entity_get_info($this->entityType);
    if (!$info) {
      throw new Exception('Entity type ' . $this->entityType . ' does not exist');
    }

    if (isset($info['bundles']) && !in_array($this->bundle, array_keys($info['bundles']))) {
      throw new Exception('Bundle ' . $this->bundle . ' for entity type ' . $this->entityType . ' does not exist');
    }

    $this->entityInfo = $info;
  }

  /**
   * Create the entity item
   */
  public function create() {
    $entity = entity_create($this->entityType, array('type' => $this->bundle));
    if ($entity) {
      $wrapper = entity_metadata_wrapper($this->entityType, $entity);
      $errors = FALSE;

      $this->updateItem($wrapper, $errors);

      if ($errors) {
        drush_log(t('Did not create !machine_name because of errors', array('!machine_name' => $this->machineName())), 'error');
        return FALSE;
      }

      $wrapper->save();
      $entity = $wrapper->value();
      $id = $this->entityInfo['entity keys']['id'];
      return array(
        'id' => $entity->{$id},
        'item' => $entity,
      );
    }
    return FALSE;
  }

  /**
   * Delete the entity item
   */
  public function delete() {
    $entity = $this->exists();

    if ($assets = $this->getAssets()) {

    }

    if ($entity) {
      // delete the entity
      $id = $this->entityInfo['entity keys']['id'];
      entity_delete($this->entityType, $entity['item']->{$id});

      // delete the map
      $this->deleteMap();
    }
  }

  /**
   * Check if the item exists.
   */
  public function exists() {
    $map = $this->getMap();
    if ($map) {
      $entity = entity_load($this->entityType, array($map['destination_id']));
      if ($entity) {
        $entity = array_shift($entity);
        return array(
          'id' => $map['destination_id'],
          'item' => $entity,
        );
      }
    }
    return FALSE;
  }

  /**
   * Update the entity item
   */
  public function update() {
    if ($entity = $this->exists()) {
      $wrapper = entity_metadata_wrapper($this->entityType, $entity['item']);
      $errors = FALSE;
      $this->updateItem($wrapper, $errors);

      if (!$errors) {
        $wrapper->save();
        $entity = $wrapper->value();
        $id = $this->entityInfo['entity keys']['id'];
        return array(
          'id' => $entity->{$id},
          'item' => $entity,
        );
      }
    }
    return FALSE;
  }

  /**
   * Update the item.
   */
  public function updateItem(&$wrapper, &$errors) {
    foreach ($this->data as $key => $value) {
      if ($key === 'id') {
        continue;
      }

      // find the taxonomy term
      try {
        $type = $wrapper->{$key}->type();
      }
      catch (EntityMetadataWrapperException $e) {
        $errors = TRUE;
        drush_log(t('Error adding value for !key on !machine_name: !message', array('!key' => $key, '!machine_name' => $this->machineName(), '!message' => $e->getMessage())), 'error');
        continue;
      }

      if ($type === 'taxonomy_term' && !is_numeric($value)) {
        $field_info = field_info_field($key);
        $vocab = $field_info['settings']['allowed_values'][0]['vocabulary'];
        $term = taxonomy_get_term_by_name($value, $vocab);
        if ($term) {
          $term = array_shift($term);
          $value = $term->tid;
        }
      }
      elseif ($type === 'text_formatted') {
        $value = array(
          'value' => $value,
          'format' => 'full_html',
        );
      }
      elseif ($type === 'list<commerce_product>') {
        if (is_string($value)) {
          $value = array($value);
        }

        $new_value = array();
        foreach ($value as $product_sku) {
          // find the product by sku
          $product = commerce_product_load_by_sku($product_sku);
          if ($product) {
            if (is_array($product)) {
              $product = array_shift($product);
            }
            array_push($new_value, $product->product_id);
          }
        }
        $value = $new_value;
      }
      elseif ($type === 'commerce_price' && !is_array($value)) {
        if (is_string($value)) {
          $value = intval($value);
        }
        $value = array(
          'amount' => $value,
          'currency_code' => 'USD',
        );
      }
      elseif ($type === 'field_item_image' || $type === 'list<field_item_image>') {
        $asset = $this->asset($value);
        $value = (array) $asset->update();
        if ($type === 'list<field_item_image>') {
          $value = array($value);
        }
        $this->assets[] = $asset;
      }

      // try to set this with entity_metadata_wrapper
      try {
        $wrapper->{$key}->set($value);
      }
      catch (EntityMetadataWrapperException $e) {
        $errors = TRUE;
        drush_log(t('Error adding value for !key on !machine_name (!type): !message', array('!key' => $key, '!machine_name' => $this->machineName(), '!message' => $e->getMessage(), '!type' => $type)), 'error');
        print $e->getTraceAsString() . "\n";
      }
    }
  }

  /**
   * Get assets.
   */
  public function getAssets() {
    return db_query('SELECT * FROM dev_content_map WHERE machine_name LIKE :name', array(':name' => db_like($this->machineName()) . '_asset_%'));
  }

}
