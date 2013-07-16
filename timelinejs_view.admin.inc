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

  $font = array(
    'Arvo-PTSans' => 'Arvo and PTSans',
    'Merriweather-NewsCycle' => 'Merriweather and NewsCycle',
    'PoiretOne-Molengo' => 'PoiretOne and Molengo',
    'PTSerif-PTSans' => 'PTSerif andPTSans',
    'DroidSerif-DroidSans' => 'DroidSerif and DroidSans',
    'Lekton-Molengo' => 'Lekton and Molengo',
    'NixieOne-Ledger' => 'Nixie One and Ledger',
    'AbrilFatface-Average' => 'Abril Fat Face and Average',
    'PlayfairDisplay-Muli' => 'Playfair Display and Muli',
    'Rancho-Gudea' => 'Ranch and Gudea',
    'Bevan-PotanoSans' => 'Bevan and Potano Sans',
    'BreeSerif-OpenSans' => 'Bree Serif and Open Sans',
    'SansitaOne-Kameron' => 'Sansita One and Kameron',
    'Pacifico-Arimo' => 'Pacifico and Arimo'
  );

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
  $form['general_settings']['timelinejs_view_font_select'] = array(
    '#type' => 'select',
    '#title' => t('Font Pair'),
    '#default_value' => variable_get('timelinejs_view_font_select', 'Arvo-PTSans'),
    '#description' => t('Please specify the font pair you choose to use'),
    '#options' => $font,
    '#required' => TRUE
  );
  $form['general_settings']['timelinejs_view_fonts'] = array(
    '#markup' => '<img src="/'.drupal_get_path('module', 'timelinejs_view').'/img/fonts.png" alt="Fonts available" />',
  );
  return system_settings_form($form);
}
