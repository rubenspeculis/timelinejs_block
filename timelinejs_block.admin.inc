<?php

/**
 * @file
 * Contains module configuration form.
 */

/**
 * Page callback: TimelineJS Config.
 *
 * @See timelinejs_block_menu()
 */
function timelinejs_block_config_form($form, &$form_state){

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
  $locale = array(
    "af" => "Afrikaans",
    "ar" => "Arabic (beta)",
    "bg" => "Bulgarian",
    "ca" => "Catalan",
    "cz" => "Czech",
    "da" => "Danish",
    "de" => "German / Deutsch",
    "el" => "Greek",
    "en" => "English",
    "es" => "Spanish",
    "eu" => "Basque / Euskara",
    "fi" => "Finnish",
    "fo" => "Faroese",
    "fr" => "French",
    "gl" => "Galician",
    "hu" => "Hungarian",
    "hy" => "Armenian",
    "id" => "Indonesian",
    "is" => "Icelandic",
    "it" => "Italian",
    "iw" => "Hebrew (beta)",
    "ja" => "Japanese",
    "ka" => "Georgian",
    "ko" => "Korean",
    "lv" => "Latvian",
    "nl" => "Dutch",
    "no" => "Norwegian",
    "pl" => "Polish",
    "pt-br" => "Brazilian Portuguese",
    "pt" => "Portuguese",
    "ru" => "Russian",
    "sk" => "Slovak",
    "sl" => "Slovenian",
    "sr-cy" => "Serbian (Cyrillic)",
    "sr" => "Serbian (Latin)",
    "sv" => "Swedish",
    "ta" => "Tamil",
    "tl" => "Tagalog",
    "tr" => "Turkish",
    "zh-cn" => "Chinese",
    "zh-tw" => "Taiwanese"
  );

  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#collabsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('General Config'),
    '#description' => t('Configuration for TimelineJS')
  );
  $form['general_settings']['timelinejs_block_number_of_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of block'),
    '#default_value' => variable_get('timelinejs_block_number_of_blocks', '2'),
    '#description' => t('Please specify the number of blocks of Timelines you wisht to use'),
    '#required' => TRUE
  );
  $form['general_settings']['timelinejs_block_font_select'] = array(
    '#type' => 'select',
    '#title' => t('Font Pair'),
    '#default_value' => variable_get('timelinejs_block_font_select', 'Arvo-PTSans'),
    '#description' => t('Please specify the font pair you choose to use'),
    '#options' => $font,
    '#required' => TRUE
  );
  $form['general_settings']['timelinejs_block_fonts'] = array(
    '#markup' => '<img src="/'.drupal_get_path('module', 'timelinejs_block').'/img/fonts.png" alt="Fonts available" />',
  );
  $form['general_settings']['timelinejs_block_locale'] = array(
    '#type' => 'select',
    '#title' => t('Location'),
    '#default_value' => variable_get('timelinejs_block_locale', 'en'),
    '#description' => t('Please specify the location you choose to use'),
    '#options' => $locale,
    '#required' => TRUE
  );
  return system_settings_form($form);
}
