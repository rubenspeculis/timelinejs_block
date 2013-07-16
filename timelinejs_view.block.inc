<?php
/**
 * @file
 * Implements various block hooks
 */

/**
 * Implement hook_block_info().
 */
function timelinejs_view_block_info(){
  $number_of_blocks = variable_get('timelinejs_view_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++) {
    $blocks['timelinejs_view_'.$i] = array(
      'info' => t('Display Timeline '.$i),
    );
  }
  return $blocks;
}

/**
 * Implement hook_block_configure().
 */
function timelinejs_view_block_configure($delta){
  $form = array();

  $date_nodes = node_load_multiple(array(),array('type' => 'timelinejs_dates'));
  $date_options = array();
  foreach($date_nodes as $date){
    $date_options[$date->nid] = $date->title;
  }

  $dates_checked = array();

  $era_nodes = node_load_multiple(array(), array('type' => 'timelinejs_era'));
  $era_oprions = array();
  foreach($era_nodes as $era){
    $era_options[$era->nid] = $era->title;
  }

  $number_of_blocks = variable_get('timelinejs_view_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_view_'.$i){
      $form['timelinejs_view_headline_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Headline'),
        '#size' => 60,
        '#description' => t('Headline for timeline'),
        '#default_value' => variable_get('timelinejs_view_headline_'.$i, 'Headline'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_intro_'.$i] = array(
        '#type' => 'textarea',
        '#title' => t('Introduction Paragraph'),
        '#description' => t('Introduction for timeline'),
        '#default_value' => variable_get('timelinejs_view_intro_'.$i, ''),
        '#required' => TRUE,
      );
      $form['timelinejs_view_title_image_'.$i] = array(
        '#type' => 'managed_file',
        '#title' => t('Media for title slide'),
        '#title_display' => 'before',
        '#description' => t('Only image files are allowed.'),
        '#upload_location' => 'public://img/',
        '#upload_validators' => array("file_validate_extensions" => array('png gif jpg')),
        '#default_value' => variable_get('timelinejs_view_title_image_'.$i, '')
      );
      $form['timelinejs_view_title_image_url_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Title Slider URL'),
        '#size' => 60,
        '#description' => t('URL for title slider. Do not use in conjuction with "Media for title slide".'),
        '#default_value' => variable_get('timelinejs_view_title_image_url_'.$i, ''),
      );
      $form['timelinejs_view_width_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 60,
        '#description' => t('Width of timeline. If using pixels then do not include the unit. If using percentage then do include the % symbol.'),
        '#default_value' => variable_get('timelinejs_view_width_'.$i, '100%'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_height_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 60,
        '#description' => t('Height of the timeline. As above.'),
        '#default_value' => variable_get('timelinejs_view_height_'.$i, '600'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_dates_'.$i] = array(
        '#type' => 'checkboxes',
        '#title' => t('Select the date nodes to appear on the timeline'),
        '#options' => $date_options,
        '#default_value' => variable_get('timelinejs_view_dates_'.$i, array())
      );
      $form['timelinejs_view_era_'.$i] = array(
        '#type' => 'checkboxes',
        '#title' => t('Select the eras to appear on the timeline'),
        '#options' => $era_options,
        '#default_value' => variable_get('timelinejs_view_era_'.$i, array())
      );
    }
  }
  return $form;
}

/**
 * Implement hook_block_save().
 */
function timelinejs_view_block_save($delta = '', $edit = array()){
  $number_of_blocks = variable_get('timelinejs_view_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_view_'.$i){
      variable_set('timelinejs_view_headline_'.$i, $edit['timelinejs_view_headline_'.$i]);
      variable_set('timelinejs_view_intro_'.$i, $edit['timelinejs_view_intro_'.$i]);
      variable_set('timelinejs_view_title_image_'.$i, $edit['timelinejs_view_title_image_'.$i]);
      variable_set('timelinejs_view_title_image_url_'.$i, $edit['timelinejs_view_title_image_url_'.$i]);
      variable_set('timelinejs_view_width_'.$i, $edit['timelinejs_view_width_'.$i]);
      variable_set('timelinejs_view_height_'.$i, $edit['timelinejs_view_height_'.$i]);
      variable_set('timelinejs_view_dates_'.$i, $edit['timelinejs_view_dates_'.$i]);
      variable_set('timelinejs_view_era_'.$i, $edit['timelinejs_view_era_'.$i]);
    }
  }
}

/**
 * Implement hook_block_view().
 */
function timelinejs_view_block_view($delta = ''){
  $number_of_blocks = variable_get('timelinejs_view_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_view_'.$i) {
      $block['subject'] = '';
      $block['content'] = timelinejs_view_block_content($i);
      return $block;
    }
  }
}

/**
 * Implements hook_block_content.
 */
function timelinejs_view_block_content($identifier = 1) {
  $library_name = 'TimelineJS';
  $width = variable_get('timelinejs_view_width_'.$identifier, '100%');
  $height = variable_get('timelinejs_view_height_'.$identifier, '600');
  $height = str_replace('px', '', $height);
  if(($library = libraries_load($library_name)) && !empty($library['loaded'])){
    $content = "<script>jQuery(document).ready(function() {\n";
    $content .= 'createStoryJS({'."\n";
    $content .= "\ttype: 'timeline',\n";
    $content .= "\twidth: '$width', height: '$height',\n";
    $content .= "\tsource: '/json/$identifier',\n";
    $content .= "\tembed_id: 'timeline_$identifier'});\n";
    $content .= "})\n";
    $content .= '</script>';
    $content .= '<div id="timeline_'.$identifier.'"></div>';
    return $content;
    }
  else {
    $error = ($library['error message']);
    drupal_set_message($error, 'error');
  }
}