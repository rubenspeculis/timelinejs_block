<?php

/**
 * @file
 * Contains module configuration form.
 */

/**
 * Page callback: TimelineJS Config.
 *
 * @See timelinejs_view_menu()
 */
function timelinejs_view_config_form($form, &$form_state){
  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#collabsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('General Config'),
    '#description' => t('Configuration for TimelineJS')
  );
  $form['general_settings']['timelinejs_view_number_of_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of block'),
    '#default_value' => variable_get('timelinejs_view_number_of_blocks', '2'),
    '#description' => t('Please specify the number of blocks of Timelines you wisht to use'),
    '#required' => TRUE
  );
  return system_settings_form($form);
}
