<?php
/**
 * @file
 * Implements various block hooks
 */

/**
 * Implement hook_block_info().
 */
function timelinejs_block_block_info(){
  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++) {
    $blocks['timelinejs_block_'.$i] = array(
      'info' => t('Display Timeline '.$i),
    );
  }
  return $blocks;
}

/**
 * Implement hook_block_configure().
 */
function timelinejs_block_block_configure($delta){
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

  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_block_'.$i){
      $intro = variable_get('timelinejs_block_intro_'.$i, array('value'=>''));
      $intro = $intro['value'];
      $form['timelinejs_block_title_slider'] = array(
        '#type' => 'fieldset',
        '#title' => t('Title Page Configuration'),
        '#weight' => 10,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE 
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_headline_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Headline'),
        '#size' => 60,
        '#description' => t('Headline for timeline'),
        '#default_value' => variable_get('timelinejs_block_headline_'.$i, 'Headline'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_intro_'.$i] = array(
        '#type' => 'text_format',
        '#title' => t('Introduction Paragraph'),
        '#description' => t('Introduction for timeline'),
        '#default_value' => $intro,
        '#format' => 'full_html',
        '#required' => TRUE,
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_title_image_'.$i] = array(
        '#type' => 'managed_file',
        '#title' => t('Title image file'),
        '#title_display' => 'before',
        '#description' => t('Only image files are allowed. Do not use if using "Title Image URL"'),
        '#upload_location' => 'public://img/',
        '#upload_validators' => array("file_validate_extensions" => array('png gif jpg')),
        '#default_value' => variable_get('timelinejs_block_title_image_'.$i, '')
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_title_image_url_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Title Image URL'),
        '#size' => 60,
        '#description' => t('URL for title slider. Do not use in conjuction with "Title image file".'),
        '#default_value' => variable_get('timelinejs_block_title_image_url_'.$i, ''),
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_title_image_credit_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Credit for title image'),
        '#size' => 60,
        '#description' => t('Credit notes for title image'),
        '#default_value' => variable_get('timelinejs_block_title_image_credit_'.$i, ''),
      );
      $form['timelinejs_block_title_slider']['timelinejs_block_title_image_caption_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Caption for title image'),
        '#size' => 60,
        '#description' => t('Caption for title image.'),
        '#default_value' => variable_get('timelinejs_block_title_image_caption_'.$i, ''),
      );
      $form['timelinejs_block_display'] = array(
        '#type' => 'fieldset',
        '#title' => t('Display Configuration'),
        '#weight' => 20,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE 
      );
      $form['timelinejs_block_display']['timelinejs_block_width_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 30,
        '#description' => t('Width of timeline. If using pixels then do not include the unit. If using percentage then do include the % symbol.'),
        '#default_value' => variable_get('timelinejs_block_width_'.$i, '100%'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_height_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#size' => 30,
        '#description' => t('Height of the timeline. As above.'),
        '#default_value' => variable_get('timelinejs_block_height_'.$i, '600'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_previous_next_bg'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Background Color for Previous/Next regions'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_previous_next_bg_'.$i, '#fff'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_previous_next_font'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Font Color for Previous/Next regions'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_previous_next_font_'.$i, '#333'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_granularity_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Select granularity'),
        '#description' => t('Select Granularity of display, Year, Year and Month, Year, Month and Day'),
        '#default_value' => variable_get('timelinejs_block_granularity_'.$i, 'ymd'),
        '#options' => array(
          'ymd' => t('Year, Month and Day'),
          'ym'  => t('Year and Month'),
          'y'   => t('Year')
        ),
        '#multiple' => FALSE,
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_start_zoom_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Set start zoom level'),
        '#description' => t('Select the starting zoom level for the timeline. Negative numbers zoom out.'),
        '#default_value' => variable_get('timelinejs_block_start_zoom_'.$i, '0'),
        '#options' => array(
          '-5' => t('-5'),
          '-4' => t('-4'),
          '-3' => t('-3'),
          '-2' => t('-2'),
          '-1' => t('-1'),
          '0' => t('0 - Default'),
          '1' => t('1'),
          '2' => t('2'),
          '3' => t('3'),
          '4' => t('4'),
          '5' => t('5'),
        ),
        '#empty_option' => t('Please make a selection'),
        '#empty_option' => '0',
        '#multiple' => FALSE,
        '#required' => TRUE,
      );
      $form['timelinejs_block_dates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Dates for Timeline'),
        '#weight' => 0,
        '#collapsible' => TRUE,
        '#collapsed' => FALSE
      );
      $form['timelinejs_block_dates']['timelinejs_block_dates_'.$i] = array(
        '#type' => 'tableselect',
        '#title' => t('Select the date nodes to appear on the timeline'),
        '#header' => $header_dates,
        '#options' => $date_options,
        '#empty' => t('No Content available'),
        '#default_value' => variable_get('timelinejs_block_dates_'.$i, array()),
        '#required' => TRUE
      );
      $form['timelinejs_block_era'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Eras for Timeline'),
        '#weight' => 15,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
      );
      $form['timelinejs_block_era']['timelinejs_block_era_'.$i] = array(
        '#type' => 'tableselect',
        '#title' => t('Select the eras to appear on the timeline'),
        '#header' => $header_eras,
        '#options' => $era_options,
        '#empty' => t('No Content available'),
        '#default_value' => variable_get('timelinejs_block_era_'.$i, array())
      );
    }
  }
  return $form;
}

/**
 * Implement hook_block_save().
 */
function timelinejs_block_block_save($delta = '', $edit = array()){
  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_block_'.$i){
      variable_set('timelinejs_block_headline_'.$i, $edit['timelinejs_block_headline_'.$i]);
      variable_set('timelinejs_block_intro_'.$i, $edit['timelinejs_block_intro_'.$i]);
      variable_set('timelinejs_block_title_image_'.$i, $edit['timelinejs_block_title_image_'.$i]);
      variable_set('timelinejs_block_title_image_url_'.$i, $edit['timelinejs_block_title_image_url_'.$i]);
      variable_set('timelinejs_block_title_image_caption_'.$i, $edit['timelinejs_block_title_image_caption_'.$i]);
      variable_set('timelinejs_block_title_image_credit_'.$i, $edit['timelinejs_block_title_image_credit_'.$i]);
      variable_set('timelinejs_block_width_'.$i, $edit['timelinejs_block_width_'.$i]);
      variable_set('timelinejs_block_height_'.$i, $edit['timelinejs_block_height_'.$i]);
      variable_set('timelinejs_block_previous_next_bg_'.$i, $edit['timelinejs_block_previous_next_bg_'.$i]);
      variable_set('timelinejs_block_previous_next_font_'.$i, $edit['timelinejs_block_previous_next_font_'.$i]);
      variable_set('timelinejs_block_granularity_'.$i, $edit['timelinejs_block_granularity_'.$i]);
      variable_set('timelinejs_block_start_zoom_'.$i, $edit['timelinejs_block_start_zoom_'.$i]);
      variable_set('timelinejs_block_dates_'.$i, $edit['timelinejs_block_dates_'.$i]);
      variable_set('timelinejs_block_era_'.$i, $edit['timelinejs_block_era_'.$i]);
    }
  }
}

/**
 * Implement hook_block_view().
 */
function timelinejs_block_block_view($delta = ''){
  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_block_'.$i) {
      $block['subject'] = '';
      $block['content'] = timelinejs_block_block_content($i);
      return $block;
    }
  }
}

/**
 * Implements hook_block_content.
 */
function timelinejs_block_block_content($identifier = 1) {
  $library_name = 'TimelineJS';
  $width = variable_get('timelinejs_block_width_'.$identifier, '100%');
  $height = variable_get('timelinejs_block_height_'.$identifier, '600');
  $height = str_replace('px', '', $height);
  $font = variable_get('timelinejs_block_font_select', 'Arvo-PTSans');
  $start_zoom = variable_get('timelinejs_block_start_zoom_'.$identifier, '0');
  if(($library = libraries_load($library_name)) && !empty($library['loaded'])){
    if($font=='other'){
      $font1 = urlencode(variable_get('timelinejs_block_font2'));
      $font2 = urlencode(variable_get('timelinejs_block_font1'));
      $path = drupal_get_path('module', 'timelinejs_block').'/css/custom_fonts_css.php?font1='.$font1.'&font2='.$font2;
      echo '<link rel="stylesheet" type="text/css" media="all" href="/'.$path.'">';
    }
    $content = "<script>jQuery(document).ready(function() {\n";
    $content .= 'createStoryJS({'."\n";
    $content .= "\ttype: 'timeline',\n";
    $content .= "\twidth: '$width', height: '$height',\n";
    $content .= "\tsource: '/json/$identifier',\n";
    $content .= "\tstart_zoom_adjust: '$start_zoom',\n";
    if($font!='other'){
      $content .= "\tfont: '$font',\n";
    }
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
