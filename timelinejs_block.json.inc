<?php

/**
 * @file
 *
 * Set the JSON feed
 */

function timelinejs_block_json($block_identifier = 1){
  $dates = _timelinejs_block_dates_generator((int)$block_identifier);
  $era =  _timelinejs_block_era_generator((int)$block_identifier);
  $headline = variable_get('timelinejs_block_headline_'.$block_identifier, 'This is a test');
  $intro = variable_get('timelinejs_block_intro_'.$block_identifier, '');
  $intro = str_replace(array("\r\n", "\r", "\n"), "", $intro['value']);
  $intro = addslashes($intro);
  $media = variable_get('timelinejs_block_title_image_'.$block_identifier);
  $media_url = variable_get('timelinejs_block_title_image_url_'.$block_identifier, '');
  $caption = variable_get('timelinejs_block_title_image_caption_'.$block_identifier, '');
  $credit = variable_get('timelinejs_block_title_image_credit_'.$block_identifier, '');

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

  header('Content-Type: application/json');
  echo($timeline);
}

function _timelinejs_block_dates_generator($block_id) {
  $block_id_dates = variable_get('timelinejs_block_dates_'.$block_id);
  $timezone = date_default_timezone();

  if(empty($block_id_dates)){
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_dates')
      ->fieldOrderBy('field_dates', 'value', 'ASC')
      ->execute();
    $nids = array_keys($result['node']);
    $nodes = node_load_multiple($nids);
  } else {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_dates')
      ->entityCondition('entity_id', $block_id_dates, 'IN')
      ->fieldOrderBy('field_dates', 'value', 'ASC')
      ->execute();
    $nids = array_keys($result['node']);
    $nodes = node_load_multiple($nids);
  }

  $dateJson = '"date":[';
  foreach($nodes as $date){
    $entry = new stdClass(); 

    $startDate = date_create($date->field_dates['und'][0]['value']);
    $endDate = date_create($date->field_dates['und'][0]['value2']);

    date_timezone_set($startDate, timezone_open($timezone));
    date_timezone_set($endDate, timezone_open($timezone));
    $adjustedStart = date_format($startDate, 'U') + date_offset_get($startDate);
    $adjustedEnd = date_format($endDate, 'U') + date_offset_get($endDate);

    $granularity = variable_get('timelinejs_block_granularity_'.$block_id, 'ymd');

    switch ($granularity) {
      case 'ymd':
        $format = 'Y,m,d';
        break;
      case 'ym':
        $format = 'Y,m';
        break;
      case 'y':
        $format = 'Y';
        break;
    }

    $entry->startDate = date($format, $adjustedStart);
    $entry->endDate = date($format, $adjustedEnd);
    $entry->headline = $date->title;
    if(isset($date->body['und'][0]['safe_value'])){
      $entry->text = $date->body['und'][0]['safe_value'];
    } else {
      $entry->text = "";
    }
    if(isset($date->field_read_more['und'][0]['value'])){
      $readmore = '<p><a href="'.$date->field_read_more['und'][0]['value'].'" title="Read More">Read More</a></p>';
      $entry->text .= $readmore;
    }
    $entry->text = str_replace(array("\r\n", "\r", "\n"), "", $entry->text);
    $entry->text = addslashes($entry->text);
    if(isset($date->field_timeline_category['und'][0]['tid'])){
      $entry->tag = taxonomy_term_load($date->field_timeline_category['und'][0]['tid'])->name;
    }
    if(isset($date->field_media['und'][0]['fid'])){
      $image = file_load($date->field_media['und'][0]['fid']); 
      $entry->asset = new stdclass();
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
      $dateJson .= '"media":"'.$entry->asset->media.'",';
      $dateJson .= '"thumbnail":"'.$entry->asset->thumbnail.'"';

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

function _timelinejs_block_era_generator($block_id) {
  $block_id_era = variable_get('timelinejs_block_era_'.$block_id);

  if(isset($block_id_era)){
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_era')
      ->entityCondition('entity_id', $block_id_era, 'IN')
      ->fieldOrderBy('field_dates', 'value', 'ASC')
      ->execute();
    $nids = array_keys($result['node']);
    $nodes = node_load_multiple($block_id_era);
  }

  if(!empty($nodes)){ 
    $eraJson = ',"era":[';

    $timezone = date_default_timezone();

    foreach($nodes as $era){
      $entry = new stdClass();
      $startDate = date_create($era->field_dates['und'][0]['value']);
      $endDate = date_create($era->field_dates['und'][0]['value2']);

      date_timezone_set($startDate, timezone_open($timezone));
      date_timezone_set($endDate, timezone_open($timezone));
      $adjustedStart = date_format($startDate, 'U') + date_offset_get($startDate);
      $adjustedEnd = date_format($endDate, 'U') + date_offset_get($endDate);

      $granularity = variable_get('timelinejs_block_granularity_'.$block_id, 'ymd');

      switch ($granularity) {
        case 'ymd':
          $format = 'Y,m,d';
          break;
        case 'ym':
          $format = 'Y,m';
          break;
        case 'y':
          $format = 'Y';
          break;
      }

      $entry->startDate = date($format, $adjustedStart);
      $entry->endDate = date($format, $adjustedEnd);

      $entry->headline = $era->title;
      $entry->text = isset($era->body['und'][0]['safe_value']) ? $era->body['und'][0]['safe_value'] : "";
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
