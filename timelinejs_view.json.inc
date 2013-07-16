<?php

/**
 * @file
 *
 * Set the JSON feed
 */

function timelinejs_view_json($block_identifier = 1){
  $dates = _timelinejs_view_dates_generator((int)$block_identifier);
  $era =  _timelinejs_view_era_generator((int)$block_identifier);
  $headline = variable_get('timelinejs_view_headline_'.$block_identifier, 'This is a test');
  $intro = variable_get('timelinejs_view_intro_'.$block_identifier, '');
  $intro = str_replace(array("\r\n", "\r", "\n"), "", $intro);
  $media = variable_get('timelinejs_view_title_image_'.$block_identifier);
  $media_url = variable_get('timelinejs_view_title_image_url_'.$block_identifier, '');
  $caption = variable_get('timelinejs_view_title_image_caption_'.$block_identifier, '');
  $credit = variable_get('timelinejs_view_title_image_credit_'.$block_identifier, '');

  if($media!=''){
    $media = file_load($media);
    $media_url = file_create_url($media->uri);
  }

  $timeline = '{"timeline":';
  $timeline .= '{';
  $timeline .= '"headline":"'. $headline .'",';
  $timeline .= '"type":"default",';
  $timeline .= '"text":"'.$intro.'",';
  if($media_url != ''){
    $timeline .= '"asset":{';
    $timeline .= '"media":"'.$media_url.'"';
    if($caption != ''){
      $timeline .= ',"caption":"'.$caption.'"';
    }
    if($credit != ''){
      $timeline .= ',"credit":"'.$credit.'"';
    }
    $timeline .= '},';
  }
  $timeline .= $dates;
  $timeline .= $era;
  $timeline .= '}}'; 

  echo($timeline);
}

function _timelinejs_view_dates_generator($block_id) {
  $block_id_dates = variable_get('timelinejs_view_dates_'.$block_id);
  if(!isset($block_id_dates)){
    $type = 'timelinejs_dates';
    $nodes = node_load_multiple(array(), array('type' => $type));
  } else {
    $nodes = node_load_multiple($block_id_dates);
  }

  $dateJson = '"date":[';
  foreach($nodes as $date){
    $entry = new stdClass(); 
    $entry->startDate = date('Y,m,d', strtotime($date->field_dates['und'][0]['value']));
    $entry->endDate = date('Y,m,d', strtotime($date->field_dates['und'][0]['value2']));
    $entry->headline = $date->title;
    $entry->text = $date->body['und'][0]['safe_value'];
    $entry->text = str_replace(array("\r\n", "\r", "\n"), "", $entry->text);
    $entry->text = addslashes($entry->text);
    if(isset($date->field_timeline_category['und'][0]['tid'])){
      $entry->tag = taxonomy_term_load($date->field_timeline_category['und'][0]['tid'])->name;
    }
    if(isset($date->field_media['und'][0]['fid'])){
      $image = file_load($date->field_media['und'][0]['fid']); 
      $entry->asset->media = file_create_url($image->uri);
      $entry->asset->thumbnail = image_style_url('timelinejs_thumb', $image->uri);
    }
    if(isset($date->field_media_url['und'][0]['value'])){
      $entry->asset->media_url = $date->field_media_url['und'][0]['value'];
    }
    if(isset($date->field_media_caption['und'][0]['value'])){
      $entry->asset->caption = $date->field_media_caption['und'][0]['value'];
    }
    if(isset($date->field_media_credit['und'][0]['value'])){
      $entry->asset->credit = $date->field_media_credit['und'][0]['value'];
    }
    if(isset($date->field_custom_class_name['und'][0]['value'])){
      $entry->class = $date->field_custom_class_name['und'][0]['value'];
    }
    $dateJson .= '{"startDate":"' . $entry->startDate .'",';
    $dateJson .= '"endDate":"' . $entry->endDate .'",';
    $dateJson .= '"headline":"' . $entry->headline .'",';
    $dateJson .= '"text":"' . $entry->text .'"';

    if(isset($entry->tag)){
      $dateJson .= ',"tag":"' . $entry->tag .'"';
    }
    if(isset($entry->class)){
      $dateJson .= ',"classname":"'.$entry->class .'"';
    }

    if(isset($entry->asset->media)){
      $dateJson .= ',"asset":{';
      $dateJson .= '"media":"'.$entry->asset->media.'"';
      $dateJson .= ',"thumbnail":"'.$entry->asset->thumbnail.'"';

      if(!isset($entry->asset->caption) && !isset($entry->asset->credit)){
        $dateJson .= '}';
      } elseif(isset($entry->asset->caption)){
          $dateJson .= ',"caption":"'.$entry->asset->caption.'"';
          if(!isset($entry->asset->credit)){
            $dateJson .= '}';
          } else {
            $dateJson .= ',"credit":"'.$entry->asset->credit.'"}';
          }
      } else {
          $dateJson .= ',"credit":"'.$entry->asset->credit.'"}';
        }
    } elseif(isset($entry->asset->media_url)){
      $dateJson .= ',"asset":{';
      $dateJson .= '"media":"'.$entry->asset->media_url.'"';

      if(!isset($entry->asset->caption) && !isset($entry->asset->credit)){
        $dateJson .= '}';
      } elseif(isset($entry->asset->caption)){
          $dateJson .= ',"caption":"'.$entry->asset->caption.'"';
          if(!isset($entry->asset->credit)){
            $dateJson .= '}';
          } else {
            $dateJson .= ',"credit":"'.$entry->asset->credit.'"}';
          }
      } else {
          $dateJson .= ',"credit":"'.$entry->asset->credit.'"}';
        }
    }

    if($date === end($nodes)){
      $dateJson .= '}]';
    } else {
      $dateJson .= '},';
    }
  }
  return $dateJson;
}

function _timelinejs_view_era_generator($block_id) {
  $block_id_era = variable_get('timelinejs_view_era_'.$block_id);
  if(!isset($block_id_era)){
    $type = 'timelinejs_era';
    $nodes = node_load_multiple(array(), array('type' => $type));
  } else {
    $nodes = node_load_multiple($block_id_era);
  }
  if(!empty($nodes)){ 
    $eraJson = ',"era":[';
    foreach($nodes as $era){
      $entry = new stdClass();
      $entry->startDate = date('Y,m,d', strtotime($era->field_dates['und'][0]['value']));
      $entry->endDate = date('Y,m,d', strtotime($era->field_dates['und'][0]['value2']));
      $entry->headline = $era->title;
      $entry->text = $era->body['und'][0]['safe_value'];
      $entry->text = str_replace(array("\r\n", "\r", "\n"), "", $entry->text);
      if(isset($era->field_timeline_category['und'][0]['tid'])){
        $entry->tag = taxonomy_term_load($era->field_timeline_category['und'][0]['tid'])->name;
      }

      $eraJson .= '{"startDate":"' . $entry->startDate . '",';
      $eraJson .= '"endDate":"' . $entry->endDate .'",';
      $eraJson .= '"headline":"' . $entry->headline .'",';
      $eraJson .= '"text":"' . $entry->text .'"';
      if(isset($entry->tag)){
        $eraJson .= ',"tag":"' . $entry->tag .'"';
      }

      if($era === end($nodes)){
        $eraJson .= '}]';
      } else {
        $eraJson .= '},';
      }
    }
    return $eraJson;
  } else {
    return '';
  }
}
