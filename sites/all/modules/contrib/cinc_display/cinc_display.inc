<?php
/**
 * @file
 * cinc_display functionality
 */

/**
 * Manages updating CINC field_instance settings.
 */
class CINCDisplay {
  public $viewMode;
  public $bundle;
  public $entityType;
  public $settings = array();
  public $lastFieldAdded = NULL;

  /**
   * Value CINCDisplay uses to increment the weight values by
   *
   * @var int
   */
  public $weightIncrement = 1;

  /**
   * The internal weight tracker
   *
   * @var int
   */
  protected $weight = 0;

  /**
   * Used for testing PHP5.2 compatibility
   */
  public $debugPHPMode = FALSE;

  /**
   * Default settings applied when you run ->field() without settings.
   *
   * @var array
   */
  public $defaultSettings = array(
    'label' => 'hidden',
    'type' => 'text_default',
    'module' => 'text',
    'settings' => array(),
    'weight' => 0,
  );

  /**
   * Factory method.
   *
   * Allows developers to override the CINCDisplay class if needed via
   * hook_cinc_init_class_name().
   */
  public static function init($bundle, $view_mode = 'default', $entity_type = 'node', $options = array()) {
    $class_name = 'CINCDisplay';
    $hook_class_name = module_invoke('cinc_display_init_class_name', $bundle, $view_mode, $entity_type);
    if ($hook_class_name && class_exists($class_name)) {
      $class_name = $hook_class_name;
    }
    return new $class_name($bundle, $view_mode, $entity_type, $options);
  }

  /**
   * Clone another display.
   *
   * @SuppressWarnings(StaticAccess)
   */
  public static function cloneDisplay($display, $bundle, $view_mode = 'default', $entity_type = 'node', $options = array()) {
    $this_display = CINCDisplay::init($bundle, $view_mode, $entity_type, $options);
    $this_display->settings = $display->settings;
    return $this_display;
  }

  /**
   * Constructor
   */
  public function __construct($bundle, $view_mode = 'default', $entity_type = 'node', $options = array()) {
    $this->bundle = $bundle;
    $this->viewMode = $view_mode;
    $this->entityType = $entity_type;
    if (isset($options['weightIncrement'])) {
      $this->weightIncrement = intval($options['weightIncrement']);
    }
  }

  /**
   * Return a simple string representation of this display.
   */
  public function __toString() {
    return $this->entityType . '.' . $this->bundle . '.' . $this->viewMode;
  }

  /**
   * Add a field.
   *
   * This is used by field(), fields(), etc. Those methods are preferred in most
   * cases but this is publically available just in case.
   */
  public function addField($field, array $settings) {
    $this->setFieldDefaults($field, $settings);
    $settings = $this->setDefaults($settings);
    if (!isset($this->settings[$field])) {
      $this->settings[$field] = array();
    }

    // set the weight to the current weight value
    $settings['weight'] = $this->weight;
    $this->settings[$field] = $settings;

    // increment the weight so the next addition gets the new weight value
    $this->weight += $this->weightIncrement;
    return $this;
  }

  /**
   * Add a field.
   *
   * There are two ways to call this method:
   *
   *   ->field(field_name, [settings])
   *   ->field(field_name, widget_type, [settings])
   */
  public function field() {
    // figure out args
    $args = func_get_args();
    $field = $args[0];
    $settings = array();

    // field(field_name)
    if (!isset($args[1])) {
      $settings = array();
    }
    // field(field_name, settings)
    elseif (isset($args[1]) && is_array($args[1])) {
      $settings = $args[1];
    }
    // field(field_name, widget_type, settings)
    elseif (isset($args[1]) && !is_array($args[1])) {
      $type_details = explode('.', $args[1]);
      $module = NULL;
      $type = $type_details[0];
      if (count($type_details) === 2) {
        $module = $type_details[0];
        $type = $type_details[1];
      }

      // check if there is an additional settings array
      if (isset($args[2]) && is_array($args[2])) {
        $settings = $args[2];
      }

      $settings['type'] = $type;
      if ($module) {
        $settings['module'] = $module;
      }
    }

    $this->lastFieldAdded = $field;
    $this->addField($field, $settings);
    return $this;
  }

  /**
   * Add multiple fields with the same settings.
   *
   * @param array $fields
   *   An array of fields to add.
   * @param array $settings
   *   Optional list of settings.
   */
  public function fields(array $fields, $settings = array()) {
    $this->lastFieldAdded = $fields;
    $settings = $this->setDefaults($settings);
    foreach ($fields as $field) {
      $this->addField($field, $settings);
    }
    return $this;
  }

  /**
   * Explicitly hide fields.
   *
   * By default, anything that is on an entity and not added will be hidden.
   * This can also be done explicitly with this method.
   *
   * @param mixed $field
   *   A field name or an array of field names.
   */
  public function hide($fields) {
    if (!is_array($fields)) {
      $fields = array($fields);
    }

    foreach ($fields as $hidden_field) {
      $this->settings[$hidden_field] = $this->setDefaults(array('type' => 'hidden'));
    }
    return $this;
  }

  /**
   * Like set() with an array, but will not merge arrays.
   *
   * This can be used in situations where you want to trump the settings already
   * added to a display field. The entire array is replaced with the supplied
   * value.
   */
  public function override($field, $settings) {
    $this->settings[$field] = $settings;
    return $this;
  }

  /**
   * Set a setting on a field that has been added.
   *
   * This can be called in several ways:
   *
   *   ->set(settings array) // uses last added field as field name
   *   ->set(setting, value) // value cannot be an array
   *   ->set(field_name, setting, value)
   *   ->set(field_name, settings array)
   *
   * The values will be merged with the existing options.
   */
  public function set() {
    $args = func_get_args();
    $args_count = count($args);

    switch ($args_count) {
      case 1:
        // pass this back with the last added field
        return $this->set($this->lastFieldAdded, $args[0]);

      case 2:
        // setting, value (cannot be an array)
        if (!is_array($args[1])) {
          return $this->set($this->lastFieldAdded, $args[0], $args[1]);
        }
        // field_name, settings array
        $field = $args[0];
        $settings = $args[1];
        break;

      case 3:
      default:
        $field = $args[0];
        $settings = array($args[1] => $args[2]);
        break;
    }

    if (isset($this->settings[$field])) {
      $this->settings[$field] = $this->setDefaults($settings, $this->settings[$field]);
    }
    return $this;
  }

  /**
   * Set default values.
   *
   * Mostly internal use, not chainable.
   */
  public function setDefaults($settings, $defaults = NULL) {
    if (!$defaults) {
      $defaults = $this->defaultSettings;
    }
    if (function_exists('array_replace_recursive') && !$this->debugPHPMode) {
      return array_replace_recursive($defaults, $settings);
    }
    return $this->setDefaultValues($defaults, $settings);
  }

  /**
   * Recursively set default values for PHP < 5.3.
   *
   * Mostly internal use, not chainable.
   */
  public function setDefaultValues($defaults, $settings) {
    foreach ($defaults as $key => $value) {
      if (!array_key_exists($key, $settings)) {
        $settings[$key] = $value;
      }
      if (is_array($value)) {
        $settings[$key] = $this->setDefaultValues($value, $settings[$key]);
      }
    }
    return $settings;
  }

  /**
   * Set field defaults based on Drupal field/instance info.
   */
  public function setFieldDefaults($field, &$settings) {
    // figure out the default formatter for this field if the type is not set
    if (function_exists('field_info_instance')) {
      if ($instance_info = field_info_instance($this->entityType, $field, $this->bundle)) {
        if (!isset($instance_info['field_type'])) {
          $instance_info['field_type'] = 'text';
        }
        $field_type_info = field_info_field_types($instance_info['field_type']);

        if (!isset($settings['type'])) {
          $settings['type'] = $field_type_info['default_formatter'];
          $settings['module'] = $field_type_info['module'];
        }
        if (!isset($settings['module'])) {
          if ($formatters = field_info_formatter_types($settings['type'])) {
            $settings['module'] = $formatters['module'];
          }
        }
      }
    }

    // figure out default settings for this type if the $settings['settings']
    // isn't set or is empty. Wrapped in function_exists so we can test outside
    // of Drupal when needed.
    if (function_exists('field_info_formatter_types')) {
      if ($formatter_settings = field_info_formatter_settings($settings['type'])) {
        if (!isset($settings['settings'])) {
          $settings['settings'] = array();
        }
        $settings['settings'] = $this->setDefaults($settings['settings'], $formatter_settings);
      }
    }
  }

  /**
   * Shortcut for adding a field's image style
   */
  public function setImageStyle($field, $style ) {
    return $this->set($field, array('settings' => array('image_style' => $style)));
  }

  /**
   * Update display settings.
   */
  public function update() {
    if (function_exists('cinc_display_apply_settings')) {
      cinc_display_apply_settings($this);
    }
    return $this;
  }
}
