<?php
/**
 * @file
 * Main DevContent Item class.
 */

/**
 * Dev content item.
 */
abstract class DevContentItem implements DevContentCrudInterface {

  public $file;
  public $id;
  public $data;

  /**
   * Constructor
   */
  public function __construct($file, $data, $file_data) {
    $this->file = $file;
    $this->id = $data['id'];
    $this->data = $data;
  }

  /**
   * Add a map entry to the existing item.
   */
  public function addMap($existing_item, $locked = FALSE) {
    db_insert('dev_content_map')
      ->fields(array(
        'machine_name' => $this->machineName(),
        'id' => $this->id,
        'file' => $this->file,
        'destination_id' => $existing_item['id'],
        'created' => time(),
        'updated' => time(),
        'locked' => intval($locked),
      ))
      ->execute();
  }

  /**
   * Create and return a new asset item.
   */
  public function asset($value) {
    $asset = new DevContentAssetItem($value);
    $asset->file = $this->file;
    $asset->id = $this->id;
    return $asset;
  }

  /**
   * Delete the map entry.
   */
  public function deleteMap() {
    db_delete('dev_content_map')
      ->condition('machine_name', $this->machineName(), '=')
      ->execute();
  }

  /**
   * Get the map entry for this item.
   */
  public function getMap() {
    if ($this->mapExists()) {
      $exists = db_query('SELECT * FROM dev_content_map WHERE machine_name=:machine_name', array(':machine_name' => $this->machineName()));
      if ($exists->rowCount() > 0) {
        return $exists->fetchAssoc();
      }
    }
    return FALSE;
  }

  /**
   * Return the machine name
   */
  public function machineName() {
    return str_replace('.yml', '', $this->file) . '_' . $this->id;
  }

  /**
   * Check if the mapped item exists.
   */
  public function mapExists() {
    $exists = db_query('SELECT * FROM dev_content_map WHERE machine_name=:machine_name', array(':machine_name' => $this->machineName()));
    if ($exists->rowCount() > 0) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Update the map entry updated time.
   */
  public function updateMap() {
    db_update('dev_content_map')
      ->fields(array('updated' => time()))
      ->condition('machine_name', $this->machineName(), '=')
      ->execute();
  }

  /**
   * Is this term locked?
   */
  public function isLocked() {
    if ($this->locked !== null) {
      return $this->locked;
    }

    $locked = db_query('SELECT locked FROM dev_content_map WHERE machine_name=:machine_name', array(':machine_name' => $this->machineName()))->fetchColumn();
    $this->locked = boolval($locked);
    return $this->locked;
  }

  public function lock() {
    if ($this->mapExists()) {
      db_update('dev_content_map')
        ->fields(array('locked' => 1))
        ->condition('machine_name', $this->machineName(), '=')
        ->execute();
    }
  }

  public function unlock() {
    if ($this->mapExists()) {
      db_update('dev_content_map')
        ->fields(array('locked' => 0))
        ->condition('machine_name', $this->machineName(), '=')
        ->execute();
    }
  }

  /**
   * Create the content item
   */
  abstract public function create();

  abstract public function exists();

  /**
   * Update the content item
   */
  abstract public function update();

  /**
   * Delete the content item
   */
  abstract public function delete();

}
