<?php
/**
 * @file
 * Implements various block hooks.
 */

require_once( dirname(__FILE__) . '/timelinejs_block.functions.inc');

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

  $date_results = _timelinejs_block_block_config_dates_options();
  $header_dates = $date_results['header_dates'];
  $date_options = $date_results['date_options'];

  $era_results = _timelinejs_block_block_config_era_options();
  $header_eras = $era_results['header'];
  $era_options = $era_results['era_options'];

  $chart_results = _timelinejs_block_block_config_chart_options();
  $header_charts = $chart_results['header'];
  $chart_options = $chart_results['chart_options'];

  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_block_'.$i){
    
      // Creates the Date table selector options
      $form['timelinejs_block_dates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Dates for Timeline'),
        '#weight' => 0,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
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

      // Form setup for Introduction Slider

      // Grab default value for introduction text
      $intro = variable_get('timelinejs_block_intro_'.$i, array('value'=>''));
      $intro = $intro['value'];

      $form['timelinejs_block_title_slider'] = array(
        '#type' => 'fieldset',
        '#title' => t('Title Slider Configuration'),
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

      // Creates the ERA select options
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
      $eras = variable_get('timelinejs_block_era_'.$i, array());
      $era_count = count(array_filter(array_values($eras)));

      $form['timelinejs_block_era'][] = _timelinejs_block_era_css_fields($era_count, $i);

      // Determines whether to show the era navigation
      $form['timelinejs_block_era']['timelinejs_block_era_nav_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Enable navigation by era'),
        '#default_value' => variable_get('timelinejs_block_era_nav_'.$i, 'yes'),
        '#options' => array(
          'yes' => t('Yes'),
          'no' => t('No')
        ),
        '#multiple' => FALSE,
        '#required' => TRUE,
      );

      // If era navigation is shown whenre should it be displayed?
      $form['timelinejs_block_era']['timelinejs_block_era_nav_display_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Where should the Era navgigation be shown?'),
        '#description' => t('The era navigation can be displayed above, below or above and below the timeline. It can be styled by editing the .era-navigation class'),
        '#default_value' => variable_get('timelinejs_block_era_nav_display_'.$i, 'below'),
        '#options' => array(
          'below' => t('Display below the timeline'),
          'above' => t('Display above the timeline'),
          'both' =>  t('Display both above and below the timeline')
        ),
        '#multiple' => FALSE,
        '#required' => TRUE,
      );

      // Creates the Chart select options
      $form['timelinejs_block_chart'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select Chart for Timeline'),
        '#weight' => 15,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
      );
      $form['timelinejs_block_chart']['timelinejs_block_chart_'.$i] = array(
        '#type' => 'tableselect',
        '#title' => t('Select the Charts to appear on the timeline'),
        '#header' => $header_charts,
        '#options' => $chart_options,
        '#empty' => t('No Content available'),
        '#default_value' => variable_get('timelinejs_block_chart_'.$i, array())
      );
      // Form Setup for Block level display configuration
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
        '#title' => t('Height'),
        '#size' => 30,
        '#description' => t('Height of the timeline. As above.'),
        '#default_value' => variable_get('timelinejs_block_height_'.$i, '600'),
        '#required' => TRUE,
      );

      //Set Start Slide
      $form['timelinejs_block_display']['timelinejs_block_starting_slide_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Starting Slide'),
        '#size' => 30,
        '#description' => t('Which slide should the timeline start at?'),
        '#default_value' => variable_get('timelinejs_block_starting_slide_'.$i, '0'),
        '#required' => TRUE,
      );


      // Display Assecibility table
      $form['timelinejs_block_display']['timelinejs_block_access_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Do you want to show the table at the bottom of this block?'),
        '#default_value' => variable_get('timelinejs_block_access_'.$i, '1'),
        '#options' => array(
          '1' => t('Yes'),
          '0' => t('No')
        ),
        '#multiple' => FALSE,
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_showCat_table_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Do you want to show the categories in the table at the bottom of this block?'),
        '#default_value' => variable_get('timelinejs_block_showCat_table_'.$i, 'yes'),
        '#options' => array(
          'yes' => t('Yes'),
          'no' => t('No')
        ),
        '#multiple' => FALSE,
        '#required' => TRUE,
      );
      // CSS Configuration for next and previous regions
      $form['timelinejs_block_display']['timelinejs_block_previous_next_bg_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Background Color for Previous/Next regions'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_previous_next_bg_'.$i, '#fff'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_previous_next_font_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Font Color for Previous/Next regions'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_previous_next_font_'.$i, '#333'),
        '#required' => TRUE,
      );

      // Configures whether to show Y, Y and M or Y, M and D
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

      // Set starting level ZOOM
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
        '#multiple' => FALSE,
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_cat_hide_'.$i] = array(
        '#type' => 'select',
        '#title' => t('Hide or show timeline category'),
        '#description' => t('Determine whether to hide or show the timeline categories.'),
        '#default_value' => variable_get('timelinejs_block_cat_hide_'.$i, 'show'),
        '#options' => array(
          'show' => t('Show'),
          'hide' => t('Hide')
        ),
        '#multiple' => FALSE,
        '#required' => FALSE,
      );
      // Set Category colors
      $form['timelinejs_block_display']['timelinejs_block_cat_odd_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Color for Odd Categories'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_cat_odd_'.$i, '#ddd'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_cat_even_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Color for Even Categories'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_cat_even_'.$i, '#999'),
        '#required' => TRUE,
      );
      $form['timelinejs_block_display']['timelinejs_block_cat_font_'.$i] = array(
        '#type' => 'textfield',
        '#title' => t('Font Color for Categories'),
        '#size' => 30,
        '#default_value' => variable_get('timelinejs_block_cat_font_'.$i, '#333'),
        '#required' => TRUE,
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
      variable_set('timelinejs_block_dates_'.$i, $edit['timelinejs_block_dates_'.$i]);
      variable_set('timelinejs_block_era_'.$i, $edit['timelinejs_block_era_'.$i]);
      variable_set('timelinejs_block_era_nav_'.$i, $edit['timelinejs_block_era_nav_'.$i]);
      variable_set('timelinejs_block_era_nav_display_'.$i, $edit['timelinejs_block_era_nav_display_'.$i]);
      variable_set('timelinejs_block_chart_'.$i, $edit['timelinejs_block_chart_'.$i]);
      variable_set('timelinejs_block_headline_'.$i, $edit['timelinejs_block_headline_'.$i]);
      variable_set('timelinejs_block_intro_'.$i, $edit['timelinejs_block_intro_'.$i]);
      variable_set('timelinejs_block_title_image_'.$i, $edit['timelinejs_block_title_image_'.$i]);
      variable_set('timelinejs_block_title_image_url_'.$i, $edit['timelinejs_block_title_image_url_'.$i]);
      variable_set('timelinejs_block_title_image_caption_'.$i, $edit['timelinejs_block_title_image_caption_'.$i]);
      variable_set('timelinejs_block_title_image_credit_'.$i, $edit['timelinejs_block_title_image_credit_'.$i]);
      variable_set('timelinejs_block_width_'.$i, $edit['timelinejs_block_width_'.$i]);
      variable_set('timelinejs_block_height_'.$i, $edit['timelinejs_block_height_'.$i]);
      variable_set('timelinejs_block_starting_slide_'.$i, $edit['timelinejs_block_starting_slide_'.$i]);
      variable_set('timelinejs_block_previous_next_bg_'.$i, $edit['timelinejs_block_previous_next_bg_'.$i]);
      variable_set('timelinejs_block_previous_next_font_'.$i, $edit['timelinejs_block_previous_next_font_'.$i]);
      variable_set('timelinejs_block_granularity_'.$i, $edit['timelinejs_block_granularity_'.$i]);
      variable_set('timelinejs_block_access_'.$i, $edit['timelinejs_block_access_'.$i]);
      variable_set('timelinejs_block_start_zoom_'.$i, $edit['timelinejs_block_start_zoom_'.$i]);
      variable_set('timelinejs_block_cat_hide_'.$i, $edit['timelinejs_block_cat_hide_'.$i]);
      variable_set('timelinejs_block_cat_odd_'.$i, $edit['timelinejs_block_cat_odd_'.$i]);
      variable_set('timelinejs_block_cat_even_'.$i, $edit['timelinejs_block_cat_even_'.$i]);
      variable_set('timelinejs_block_showCat_table_'.$i, $edit['timelinejs_block_showCat_table_'.$i]);
      variable_set('timelinejs_block_cat_font_'.$i, $edit['timelinejs_block_cat_font_'.$i]);
      _timelinejs_block_era_css_save($i, $edit);
    }
  }
}

/**
 * Implement hook_block_view().
 */
function timelinejs_block_block_view($delta = ''){
  $number_of_blocks = variable_get('timelinejs_block_number_of_blocks', '2');
  for($i=1; $i<=$number_of_blocks; $i++){
    if($delta === 'timelinejs_block_'.$i && user_access('access timelinejs block')) {
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
  $starting_slide = variable_get('timelinejs_block_starting_slide_'.$identifier, '0');
  $start_zoom = variable_get('timelinejs_block_start_zoom_'.$identifier, '0');

  $previous_next_bg = urlencode(variable_get('timelinejs_block_previous_next_bg_'.$identifier, '#fff'));
  $previous_next_font = urlencode(variable_get('timelinejs_block_previous_next_font_'.$identifier, '#ddd'));
  $previous_next_css_path = '/'.drupal_get_path('module', 'timelinejs_block').'/css/custom_previous_next_css.php?bg='.$previous_next_bg.'&font='.$previous_next_font;

  $access = variable_get('timelinejs_block_access_'.$identifier, '1');

  $eras = variable_get('timelinejs_block_era_'.$identifier); 
  $eras = array_filter($eras);
  if(!empty($eras)) {
    $era_count = count($eras);
    $era_css = array();
    for($i=1; $i<=$era_count; $i++){
      $color = variable_get('timelinejs_block_era_'.$i.'_css_'.$identifier);
      if(isset($color)){
        $era_css['era'.$i] = $color;
      }
    }
  }
  if(variable_get('timelinejs_block_era_nav_'.$identifier, 'yes') == 'yes') {
    $date_era_matcher = _timelinejs_era_date_matcher();
    $era_nav_display = variable_get('timelinejs_block_era_nav_display_'.$identifier); 
  } else {
    $date_era_matcher = FALSE;
    $era_nav_display = FALSE;
  }

  $cat_odd_color = urlencode(variable_get('timelinejs_block_cat_odd_'.$identifier, '#ddd'));
  $cat_even_color = urlencode(variable_get('timelinejs_block_cat_even_'.$identifier, '#999'));
  $cat_font_color = urlencode(variable_get('timelinejs_block_cat_font_'.$identifier, '#333'));
  $cat_hide_category = urlencode(variable_get('timelinejs_block_cat_hide_'.$identifier, 'hide'));

  $cat_color_css_path = '/'.drupal_get_path('module','timelinejs_block').'/css/custom_category_css.php?';
  $cat_color_css_path .= 'oddcolor='.$cat_odd_color.'&evencolor='.$cat_even_color.'&catfontcolor='.$cat_font_color.'&catDisplay='.$cat_hide_category;
  $nav_css_path = '/'.drupal_get_path('module','timelinejs_block').'/css/custom_timeline_nav.php?';

  if(($library = libraries_load($library_name)) && !empty($library['loaded'])){
    if(!empty($era_css)){
      $era_css_parameters = '?';
      foreach($era_css as $class => $color){
        $era_css_parameters .= $class .'='. urlencode($color).'&';
      }
      $era_css_path = '/'.drupal_get_path('module', 'timelinejs_block').'/css/custom_era_css.php'.$era_css_parameters;
      drupal_add_css($era_css_path);
    }
    if($font=='other'){
      $font1 = urlencode(variable_get('timelinejs_block_font2'));
      $font2 = urlencode(variable_get('timelinejs_block_font1'));
      $path = '/'.drupal_get_path('module', 'timelinejs_block').'/css/custom_fonts_css.php?font1='.$font1.'&font2='.$font2;
      drupal_add_css($path);
    }
    drupal_add_css($previous_next_css_path);
    drupal_add_css($cat_color_css_path);
    drupal_add_css($nav_css_path);

    $content = "<script>jQuery(document).ready(function() {\n";
    $content .= 'createStoryJS({'."\n";
    $content .= "\ttype: 'timeline',\n";
    $content .= "\twidth: '$width', height: '$height',\n";
    $content .= "\tsource: '/json/$identifier',\n";
    $content .= "\tstart_at_slide: '$starting_slide',\n";
    $content .= "\tpreload: '100',\n";
    $content .= "\tstart_zoom_adjust: '$start_zoom',\n";
    $content .= "\thash_bookmark: true,\n";
    if($font!='other'){
      $content .= "\tfont: '$font',\n";
    }
    $content .= "\tembed_id: 'timeline_$identifier'});\n";
    $content .= "})\n";
    $content .= '</script>';
    // Era Nav above the timeline
    if($era_nav_display == 'above' || $era_nav_display == 'both'){
      if($date_era_matcher != FALSE){
        $content .= "\t".$date_era_matcher."\n";
      }
    }
    // Timeline DIV
    $content .= '<div class="access"><a href="#access">Jump to accessible version</a></div>';
    $content .= '<div id="timeline_'.$identifier.'"></div>';
    // Era nav below the timeline
    if($era_nav_display == 'below' || $era_nav_display == 'both'){
      if($date_era_matcher != FALSE){
        $content .= "\t".$date_era_matcher."\n";
      }
    }
    if($access == 1) {
      $table = _timelinejs_block_table_generator($identifier);
      $content .= '<a name="access"><div id="timeline_table_'.$identifier.'" class="timelinejs_table">';
      $content .= $table;
      $content .= '</div>';
    }
    return $content;
    }
  else {
    $error = ($library['error message']);
    drupal_set_message($error, 'error');
  }
}
