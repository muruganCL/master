<?php
module_load_include('inc', 'lulzbot_dev_content', 'includes/entity');

/**
 * Manage node items.
 */
class DevContentNodeItem extends DevContentEntityItem {
  public $entityType;
  public $bundle;

  /**
   * Check if the item exists.
   */
  public function exists() {
    $map = $this->getMap();
    if ($map) {
      $node = node_load($map['destination_id']);
      if ($node) {
        return array(
          'id' => $map['destination_id'],
          'item' => $node,
        );
      }
    }
    return FALSE;
  }

}
