<?php
/**
 * @file
 * Asset classes for images and files.
 */

/**
 * Class for managing assets like files & images that are tied to content items.
 */
class DevContentAssetItem extends DevContentItem {
  public $localUrl;
  public $url;

  public $pathDetails = array();
  public $assetFile = NULL;

  /**
   * Construct the asset item.
   */
  public function __construct($url) {
    lulzbot_dev_content_assert_upload_directory();

    $this->pathDetails['url'] = $this->pathDetails['path'] = NULL;
    $this->url = $url;
  }

  /**
   * Get the asset machine name.
   */
  public function machineName() {
    return str_replace('.yml', '', $this->file) . '_' . $this->id . '_asset_' . sha1($this->url);
  }

  /**
   * Override adding the map entry.
   */
  public function addMap($existing_item, $locked = FALSE) {
    db_insert('dev_content_map')
      ->fields(array(
        'machine_name' => $this->machineName(),
        'id' => $this->id,
        'file' => $this->file,
        'destination_id' => $existing_item->fid,
        'created' => time(),
        'updated' => time(),
        'locked' => intval($locked),
      ))
      ->execute();
  }

  /**
   * Assert that the referenced file exists.
   */
  public function assertFile() {
    $this->setPathDetails();
    $path = $this->pathDetails['path'];
    $file_path = $this->assetPath($path['basename']);

    // copy the file locally
    if (!$this->fileExists()) {
      copy($this->url, $file_path);
    }

    // check if there is a managed file record already.
    if ($exists = $this->managedFileExists()) {
      $this->assetFile = (object) $exists;
      return;
    }

    // save a managed file reference
    $file = new stdClass();
    $file->uid = 1;
    $file->uri = $file_path;
    $file->filename = basename($file_path);
    $file->filemime = file_get_mimetype($file_path);
    $file->filesize = filesize($file_path);
    $file->status = FILE_STATUS_PERMANENT;
    $file->display = '1';
    file_save($file);
    $this->assetFile = $file;
  }

  /**
   * Get local path for the file.
   *
   * @param string $basename
   *   The basename for the file.
   */
  public function assetPath($basename) {
    return 'public://dev_content_assets/' . $basename;
  }

  /**
   * Check if the file exists.
   */
  public function fileExists() {
    $this->setPathDetails();
    return file_exists($this->assetPath($this->pathDetails['path']['basename']));
  }

  /**
   * Check if the map entry exists.
   */
  public function mapExists() {
    $exists = db_query('SELECT * FROM dev_content_map WHERE machine_name=:machine_name', array(':machine_name' => $this->machineName()));
    if ($exists->rowCount() > 0) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Check if the managed file exists.
   */
  public function managedFileExists() {
    $file_path = $this->assetPath($this->pathDetails['path']['basename']);
    return db_query('SELECT * FROM file_managed WHERE uri=:uri', array(':uri' => $file_path))->fetchAssoc();
  }

  /**
   * Set the internal path details for a remote URL.
   */
  public function setPathDetails() {
    if ($this->urlIsRemote()) {
      $this->pathDetails['url'] = parse_url($this->url);
      $this->pathDetails['path'] = pathinfo($this->pathDetails['url']['path']);
      return $this->pathDetails;
    }

    $this->pathDetails['path'] = pathinfo($this->url);
    return $this->pathDetails;
  }

  /**
   * Check if the URL is a stream path (http, etc.)
   */
  public function urlIsRemote() {
    return !stream_is_local($this->url);
  }

  /**
   * Create an asset.
   */
  public function create() {
    $this->assertFile();

    if (!$this->mapExists()) {
      $this->addMap($this->assetFile);
    }
    else {
      $this->updateMap();
    }

    return $this->assetFile;
  }

  /**
   * Update the asset.
   */
  public function update() {
    return $this->create();
  }

  /**
   * Check out if the asset is still around.
   */
  public function exists() {
    // check if the file exists
    $this->setPathDetails();

    // check if the db record exists.
    if (!$this->mapExists()) {
      return FALSE;
    }

    // if the local file does not exist, return FALSE.
    if (!$this->fileExists()) {
      return FALSE;
    }

    // does managed file record still exist?
    if (!$this->managedFileExists()) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Remove the asset.
   */
  public function delete() {

  }

}

class DevContentFileAsset extends DevContentAssetItem {

}

class DevContentImageAsset extends DevContentAssetItem {

}
