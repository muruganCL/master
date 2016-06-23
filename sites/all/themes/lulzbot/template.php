<?php
/**
 * @file
 * Template stuff.
 */

/**
 * Include .inc files.
 */
$include_files = array(
  'block',
  'boxes',
  'breadcrumb',
  'comment',
  'field',
  'form',
  'menu',
  'node',
  'page',
  'html',
  'javascript',
  'entity',
  'view',
);

foreach ($include_files as $filename) {
  include 'inc/' . $filename . '.inc';
}
