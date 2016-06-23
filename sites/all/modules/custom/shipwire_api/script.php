<?php

if (php_sapi_name() !== 'cli') {
  exit;
}

$data = array (
  'options' =>
  array (
    'currency' => 'USD',
    'canSplit' => 1,
    'warehouseArea' => 'us',
  ),
  'order' =>
  array (
    'shipTo' =>
    array (
      'address1' => '3507 Ringsby Ct Ste 111',
      'address2' => '',
      'city' => 'Denver',
      'region' => 'CO',
      'country' => 'US',
      'isCommerical' => 1,
    ),
    'items' =>
    array (
      0 =>
      array (
        'sku' => 'tshirt-black-us',
        'quantity' => 1,
      ),
    ),
  ),
);

// $data = array(
//   'options' => array(
//     'currency' => 'USD',
//     'canSplit' => 1,
//     'warehouseArea' => 'us',
//   ),
//   'order' => array(
//     'shipTo' => array(
//       'address1' => '3507 Ringsby Ct',
//       'address2' => 'Suite 111',
//       'city' => 'Denver',
//       'region' => 'CO',
//       'country' => 'US',
//       'isCommerical' => 1,
//     ),
//     'items' => array(
//       array(
//         'sku' => 'tshirt-black-um',
//         'quantity' => 1,
//       ),
//     ),
//   ),
// );
// echo json_encode($data);

$shipwire = shipwire_api_request();
var_dump($shipwire->post()->debug()->rate($data));
