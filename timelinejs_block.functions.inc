<?php
/**
 * @file
 * Functions to generate accessible content.
 */

/**
 * Function to return table of JSON file.
 */
function _timelinejs_block_table_generator($block_id = '1') {

  $showCat = variable_get('timelinejs_block_showCat_table_'.$block_id, 'no');

  // Configure Header Row
  $header_row = "<tr>";
  $header_row .= "<th>Date</th>";
  if('yes' == $showCat){
    $header_row .= "<th>Category</th>";
  }
  $header_row .= "<th>Title</th>";
  $header_row .= "<th>Summary Text</th>";
  $header_row .= "</tr>";

  $json = _timelinejs_block_table_json_parse($block_id);
  $dates = $json['dates'];
  $date_rows = '';
  foreach($dates as $date){
    $date_rows .= "<tr>";
    $startDate = strtotime(str_replace(',','-',$date->startDate));
    $date_rows .= "<td>".date('Y/m/d', $startDate)."</td>";
    if('yes' == $showCat){
      if(isset($date->tag) && !empty($date->tag)){
        $date_rows .= "<td>".$date->tag."</td>";
      } else {
        $date_rows .= "<td>&nbsp;</td>";
      }
    }
    $date_rows .= "<td>".$date->headline."</td>";
    $date_rows .= "<td>".$date->text."</td>";
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

// Function to build tableselect era options in block config.
function _timelinejs_block_block_config_era_options() {

  $header_eras = array(
    'e_title' => array('data' => t('Era Title'), 'field' => 'ne.title'),
    'e_startDate' => array('data' => t('Era Start Date'), 'field' => 'de.field_dates_value'),
    'e_endDate' => array('data' => t('Era End Date'), 'field' => 'de.field_dates_value2'),
    'e_status' => array('data' => t('Era Status'), 'field' => 'ne.status'),
  );
  $query = db_select('node', 'ne');
  $query->join('field_data_field_dates', 'de', 'ne.nid = de.entity_id');
  $eras_nids = $query
    ->fields('ne', array('nid'))
    ->fields('de', array('field_dates_value'))
    ->fields('de', array('field_dates_value2'))
    ->extend('TableSort')
    ->orderByHeader($header_eras)
    ->execute()
    ->fetchCol();

  $era_nodes = node_load_multiple($eras_nids, array('type' => 'timelinejs_era'));
  $era_options = array();
  foreach($era_nodes as $era){
    $era_options[$era->nid] = array(
      'e_title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $era->title,
          '#href' => 'node/'.$era->nid,
        )
      ),
      'e_startDate' => date('Y-m-d', strtotime($era->field_dates['und'][0]['value'])),
      'e_endDate' => date('Y-m-d', strtotime($era->field_dates['und'][0]['value2'])),
      'e_status' => $era->status ? t('Published') : t('Not Published'),
    );
  }
  $results = array(
    'header' => $header_eras,
    'era_options' => $era_options
  );
  return $results;
}

// Function to build table select for dates in block config.
function _timelinejs_block_block_config_dates_options() {

  $header_dates = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'startDate' => array('data' => t('Start Date'), 'field' => 'd.field_dates_value'),
    'endDate' => array('data' => t('End Date'), 'field' => 'd.field_dates_value2'),
    'status' => array('data' => t('Status'), 'field' => 'n.status'),
  );
  $query = db_select('node', 'n');
  $query->join('field_data_field_dates', 'd', 'n.nid = d.entity_id');
  $dates_nids = $query
    ->fields('n', array('nid'))
    ->fields('d', array('field_dates_value'))
    ->fields('d', array('field_dates_value2'))
    ->extend('TableSort')
    ->orderByHeader($header_dates)
    ->execute()
    ->fetchCol();
  $date_nodes = node_load_multiple($dates_nids,array('type' => 'timelinejs_dates'));
  $date_options = array();
  foreach($date_nodes as $date){
    $date_options[$date->nid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $date->title,
          '#href' => 'node/'.$date->nid,
        )
      ),
      'startDate' => date('Y-m-d', strtotime($date->field_dates['und'][0]['value'])),
      'endDate' => date('Y-m-d', strtotime($date->field_dates['und'][0]['value2'])),
      'status' => $date->status ? t('Published') : t('Not Published'),
    );
  }
  $results = array(
    'header_dates' => $header_dates,
    'date_options' => $date_options
  );
  return $results;
}

/**
 * function to build era css fields dynamically.
 */
function _timelinejs_block_era_css_fields($number_of_eras_selected = 0, $block_id) {

  for($i=1; $i<=$number_of_eras_selected; $i++) {
    $form['timelinejs_block_era']['timelinejs_block_era_'.$i.'_css_'.$block_id] = array(
      '#type' => 'textfield',
      '#title' => 'Color for era '.$i,
      '#size' => 30,
      '#default_value' => variable_get('timelinejs_block_era_'.$i.'_css_'.$block_id, '#333333'),
    );
  }
  if(isset($form['timelinejs_block_era'])){
    return $form['timelinejs_block_era'];
  }
}

function _timelinejs_block_era_css_save($block_id, $edit) {

  $eras = variable_get('timelinejs_block_era_'.$block_id, array());
  $era_count = count(array_filter(array_values($eras)));

  for($i=1; $i<=$era_count; $i++) {
    if(isset($edit['timelinejs_block_era_'.$i.'_css_'.$block_id])){
      variable_set('timelinejs_block_era_'.$i.'_css_'.$block_id, $edit['timelinejs_block_era_'.$i.'_css_'.$block_id]);
    }
  }
}

/**
 * Cleanner
 */

function _ms_to_UTF8_convert($string) {
  $search = array(
    "\xe2\x80\x98",
    "\xe2\x80\x99",
    "\xe2\x80\x9c",
    "\xe2\x80\x9d",
    "\xe2\x80\x93",
    "\xe2\x80\x94",
    "\xe2\x80\xa6",
    chr(145),
    chr(146),
    chr(147),
    chr(148),
    chr(150),
    chr(151),
    chr(133)
  );
  $replace = array(
    "'",
    "'",
    '"',
    '"',
    '-',
    '--',
    '...',
    "'",
    "'",
    '"',
    '"',
    '-',
    '--',
    '...'
  );
  $string = str_replace($search, $replace, $string);
  $string = iconv('UTF-8', 'ASCII//TRANSLIT', $string);
  return $string;
}
