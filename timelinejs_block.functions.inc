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

  // Construct Table
  $table = "<table>";
  $table .= $header_row;
  $table .= "</table>";

  return $table;
}
