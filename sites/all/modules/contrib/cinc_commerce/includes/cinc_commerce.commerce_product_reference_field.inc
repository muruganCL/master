<?php

/**
 * Creates commerce product reference field
 *
 * @code
 * $my_field = CINC::init('CommerceProductReferenceField')->set('field_name', 'my_field');
 * @endcode
 */
class CINC_CommerceProductReferenceField extends CINC_Field {

  public static $dependencies = array('field', 'commerce_product_reference');
  public static $field_types = array('commerce_product_reference');

  function __construct() {

    parent::__construct();

    $this->config_filters['cardinality'] = 'set_cardinality';

    $this
      ->set('type', 'commerce_product_reference')
      ->set('module', 'commerce_product_reference')
      ->set('label', t('Product Reference'))
      ->set('description', t('This field reference another product.'))
      ->set('settings', array())
      ->set('instance_settings', array(
        'referenceable_types' => array(),
        'field_injection' => TRUE,
      ))
      ->set('default_widget', 'options_select')
      ->set('default_formatter', 'commerce_product_reference_title_link')
      ->set('property_callbacks', array('commerce_product_reference_property_info_callback'));
  }

  /**
   * Set the cardinality
   */
  public function set_cardinality(&$cardinality) {
    if ($cardinality == 0) {
      $cardinality = -1;
    }
    return TRUE;
  }

  /**
   * Add a referenceable type.
   */
  public function add_type($type) {
    $types = $this->get('instance_settings.referenceable_types');
    $types[$type] = $type;
    $this->set_instance('settings.referenceable_types', $types);
    return $this;
  }

  /**
   * Add multiple types.
   *
   * @param array $types
   *   An array of types to add.
   */
  public function add_types(array $types) {
    foreach ($types as $type) {
      $this->add_type($type);
    }
    return $this;
  }

}
