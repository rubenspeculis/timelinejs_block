<?php
/**
 * @file
 * Functions to generate accessible content.
 */

/**
 * Function to return table of JSON file.
 */
function _timelinejs_block_table_generator($block_id = '1') {
  // Configure Header Row
  $header_row = "<tr>";
  $header_row .= "<th>Date</th>";
  $header_row .= "<th>Category</th>";
  $header_row .= "<th>Title</th>";
  $header_row .= "<th>Summary Text</th>";
  $header_row .= "</tr>";

  $json = _timelinejs_block_table_json_parse($block_id);
  $dates = $json['dates'];
  $date_rows = '';
  foreach($dates as $date){
    $date_rows .= "<tr>";
    $date_rows .= "<td>".$date['startDate']."</td>";
    $date_rows .= "<td>".$date['tag']."</td>";
    $date_rows .= "<td>".$date['headline']."</td>";
    $date_rows .= "<td>".addslashes($date['text'])."</td>";
    $date_rows .= "</tr>";
  }

  // Construct Table
  $table = "<table>";
  $table .= $header_row;
  $table .= $date_rows;
  $table .= "</table>";

  $html = '<h2>'.$json['timeline']->headline.'</h2>';
  $html .= '<p>'.$json['timeline']->text.'</p>';
  $html .= $table;

  return $html;
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
    exit();
  }

  $dates = $json->timeline->date;

  // Convert objects to array for sorting with uasort();
  foreach($dates as $key => $date) {
    $dates[$key] = (array)$date;
  }
  usort($dates, "_timelinejs_block_sort");

  $results = array(
    'timeline' => $json->timeline,
    'dates' => $dates
  );

  return $results;

}

// Sort function
function _timelinejs_block_sort($i, $j) {
  $a = $i['startDate'];
  $b = $j['startDate'];
  if ($a == $b) return 0;
  if ($a > $b) return 1;
  else return -1;
}

// Sort function NODES
function _timelinejs_block_era_sort($i, $j) {
  $a = $i['field_dates']['und'][0]['value'];
  $b = $j['field_dates']['und'][0]['value'];
  if ($a == $b) return 0;
  if ($a > $b) return 1;
  else return -1;
}

// Function to test if string is valid JSON
function _timelinejs_block_isJson($string) {
   json_decode($string);
    return (json_last_error() == JSON_ERROR_NONE);
}
