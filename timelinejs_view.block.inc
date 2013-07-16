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

  $header_dates = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'startDate' => array('data' => t('Start Date'), 'field' => 'd.field_dates_value'),
    'endDate' => array('data' => t('End Date'), 'field' => 'd.field_dates_value2'),
    'category' => array('data' => t('Category') , 'field' => 'c.field_timeline_category_tid'),
    'status' => array('data' => t('Status'), 'field' => 'n.status'),
  );
  $query = db_select('node', 'n');
  $query->join('field_data_field_dates', 'd', 'n.nid = d.entity_id');
  $query->join('field_data_field_timeline_category', 'c', 'n.nid = c.entity_id');
  $dates_nids = $query
    ->fields('n', array('nid'))
    ->fields('d', array('field_dates_value'))
    ->fields('d', array('field_dates_value2'))
    ->fields('c', array('field_timeline_category_tid'))
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
      'category' => taxonomy_term_load($date->field_timeline_category['und'][0]['tid'])->name,
      'status' => $date->status ? t('Published') : t('Not Published'),
    );
  }

  $dates_checked = array();

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
  $era_oprions = array();
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

  $number_of_blocks = variable_get('timelinejs_view_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_view_'.$i){
      $intro = variable_get('timelinejs_view_intro_'.$i, array('value'=>''));
      $intro = $intro['value'];
      $form['timelinejs_view_title_slider'] = array(
        '#type' => 'fieldset',
        '#title' => t('Title Page Configuration'),
        '#weight' => 10,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE 
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_headline_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Headline'),
        '#size' => 60,
        '#description' => t('Headline for timeline'),
        '#default_value' => variable_get('timelinejs_view_headline_'.$i, 'Headline'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_intro_'.$i] = array(
        '#type' => 'text_format',
        '#title' => t('Introduction Paragraph'),
        '#description' => t('Introduction for timeline'),
        '#default_value' => $intro,
        '#format' => 'full_html',
        '#required' => TRUE,
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_title_image_'.$i] = array(
        '#type' => 'managed_file',
        '#title' => t('Title image file'),
        '#title_display' => 'before',
        '#description' => t('Only image files are allowed. Do not use if using "Title Image URL"'),
        '#upload_location' => 'public://img/',
        '#upload_validators' => array("file_validate_extensions" => array('png gif jpg')),
        '#default_value' => variable_get('timelinejs_view_title_image_'.$i, '')
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_title_image_url_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Title Image URL'),
        '#size' => 60,
        '#description' => t('URL for title slider. Do not use in conjuction with "Title image file".'),
        '#default_value' => variable_get('timelinejs_view_title_image_url_'.$i, ''),
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_title_image_credit_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Credit for title image'),
        '#size' => 60,
        '#description' => t('Credit notes for title image'),
        '#default_value' => variable_get('timelinejs_view_title_image_credit_'.$i, ''),
      );
      $form['timelinejs_view_title_slider']['timelinejs_view_title_image_caption_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Caption for title image'),
        '#size' => 60,
        '#description' => t('Caption for title image.'),
        '#default_value' => variable_get('timelinejs_view_title_image_caption_'.$i, ''),
      );
      $form['timelinejs_view_display'] = array(
        '#type' => 'fieldset',
        '#title' => t('Display Configuration'),
        '#weight' => 20,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE 
      );
      $form['timelinejs_view_display']['timelinejs_view_width_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 60,
        '#description' => t('Width of timeline. If using pixels then do not include the unit. If using percentage then do include the % symbol.'),
        '#default_value' => variable_get('timelinejs_view_width_'.$i, '100%'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_display']['timelinejs_view_height_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 60,
        '#description' => t('Height of the timeline. As above.'),
        '#default_value' => variable_get('timelinejs_view_height_'.$i, '600'),
        '#required' => TRUE,
      );
      $form['timelinejs_view_dates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Dates for Timeline'),
        '#weight' => 0,
        '#collapsible' => TRUE,
        '#collapsed' => FALSE
      );
      $form['timelinejs_view_dates']['timelinejs_view_dates_'.$i] = array(
        '#type' => 'tableselect',
        '#title' => t('Select the date nodes to appear on the timeline'),
        '#header' => $header_dates,
        '#options' => $date_options,
        '#empty' => t('No Content available'),
        '#default_value' => variable_get('timelinejs_view_dates_'.$i, array()),
        '#required' => TRUE
      );
      $form['timelinejs_view_era'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Eras for Timeline'),
        '#weight' => 15,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
      );
      $form['timelinejs_view_era']['timelinejs_view_era_'.$i] = array(
        '#type' => 'tableselect',
        '#title' => t('Select the eras to appear on the timeline'),
        '#header' => $header_eras,
        '#options' => $era_options,
        '#empty' => t('No Content available'),
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
      variable_set('timelinejs_view_title_image_caption_'.$i, $edit['timelinejs_view_title_image_caption_'.$i]);
      variable_set('timelinejs_view_title_image_credit_'.$i, $edit['timelinejs_view_title_image_credit_'.$i]);
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
