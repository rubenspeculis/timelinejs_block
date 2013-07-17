<?php
/**
 * @file
 * Functions to generate accessible content.
 */

/**
 * Function to return table of JSON file.
 */
function _timelinejs_block_table_generator($block_indetifier = '1') {
  // Configure Header Row
  $header_row = "<tr>";
  $header_row .= "<th>Date</th>";
  $header_row .= "<th>Title</th>";
  $header_row .= "<th>Sumary Text</th>";
  $header_row .= "</tr>";

  _timelinejs_block_table_json_parse('1');

  // Construct Table
  $table = "<table>";
  $table .= $header_row;
  $table .= "</table>";

  return $table;
}

/**
 * Function to process JSON file
 */
function _timelinejs_block_table_json_parse($block_identifier = '1') {
  global $base_url;
  $json_path = $base_url . '/json/' . $block_identifier;
  $json = file_get_contents($json_path);
  $isJson = _timelinejs_block_isJson($json);
  if($isJson) {
    $json = json_decode($json);
  } else {
    drupal_set_message('JSON parsing failed', 'error');
  }
  //dump($json);

}


// Function to test if string is valid JSON
function _timelinejs_block_isJson($string) {
   json_decode($string);
    return (json_last_error() == JSON_ERROR_NONE);
}
