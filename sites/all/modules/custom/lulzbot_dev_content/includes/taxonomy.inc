<?php
module_load_include('inc', 'lulzbot_dev_content', 'lulzbot_dev_content.content');

/**
 * Manage taxonomy items.
 */
class DevContentTaxonomyItem extends DevContentItem {
  public $vocabulary;

  /**
   * Constructor
   */
  public function __construct($file, $data, $file_data) {
    parent::__construct($file, $data, $file_data);
    $this->vocabulary = $file_data['vocabulary'];
  }

  /**
   * Create the taxonomy item
   */
  public function create() {
    $vocabs = taxonomy_vocabulary_get_names();
    $term = (object) array(
      'name' => $this->data['name'],
      'vid' => $vocabs[$this->vocabulary]->vid,
    );
    taxonomy_term_save($term);
    return array(
      'id' => $term->tid,
      'item' => $term,
    );
  }

  /**
   * Delete the taxonomy item
   */
  public function delete() {

  }

  /**
   * Check if the item exists.
   */
  public function exists() {
    $term = taxonomy_get_term_by_name($this->data['name'], $this->vocabulary);
    if ($term) {
      $this_term = array_shift($term);
      return array(
        'id' => $this_term->tid,
        'item' => $this_term,
      );
    }

    return FALSE;
  }

  /**
   * Update the taxonomy term
   */
  public function update() {
    if ($existing = $this->exists()) {
      if ($this->isLocked()) {
        return $existing;
      }

      $term = $existing['item'];
      $term->name = $this->data['name'];
      taxonomy_term_save($term);
      return array(
        'id' => $term->tid,
        'item' => $term,
      );
    }
    return FALSE;
  }

}
