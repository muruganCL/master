<?php
/**
 * Dev Content CRUD interface definition.
 */
interface DevContentCrudInterface {
  /**
   * Create the content item
   */
  public function create();

  public function exists();

  /**
   * Update the content item
   */
  public function update();

  /**
   * Delete the content item
   */
  public function delete();

}
