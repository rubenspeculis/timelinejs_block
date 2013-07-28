<?php

/**
 * @file
 *
 * Set the JSON feed
 */

require_once( dirname(__FILE__) . '/timelinejs_block.functions.inc');

function timelinejs_block_json($block_identifier = 1){
  $dates = _timelinejs_block_dates_generator((int)$block_identifier);
  $era =  _timelinejs_block_era_generator((int)$block_identifier);
  $chart =  _timelinejs_block_chart_generator((int)$block_identifier);
  $headline = json_encode(variable_get('timelinejs_block_headline_'.$block_identifier, 'This is a test'));

  $intro = variable_get('timelinejs_block_intro_'.$block_identifier, '');
  $intro = json_encode($intro['value']);

  $media = variable_get('timelinejs_block_title_image_'.$block_identifier);
  $media_url = json_encode(variable_get('timelinejs_block_title_image_url_'.$block_identifier, ''));

  $caption = json_encode(variable_get('timelinejs_block_title_image_caption_'.$block_identifier, ''));
  $credit = json_encode(variable_get('timelinejs_block_title_image_credit_'.$block_identifier, ''));

  if($media!=''){
    $media = file_load($media);
    $media_url = json_encode(file_create_url($media->uri));
  }

  $timeline = '{"timeline":';
  $timeline .= '{';
  $timeline .= '"headline":'. $headline .',';
  $timeline .= '"type":"default",';
  $timeline .= '"text":'.$intro.',';
  if($media_url != ''){
    $timeline .= '"asset":{';
    $timeline .= '"media":'.$media_url;
    if($caption != ''){
      $timeline .= ',"caption":'.$caption;
    }
    if($credit != ''){
      $timeline .= ',"credit":'.$credit;
    }
    $timeline .= '},';
  }
  $timeline .= $dates;
  $timeline .= $era;
  $timeline .= $chart;
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
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_dates')
      ->entityCondition('entity_id', $block_id_dates, 'IN')
      ->fieldOrderBy('field_dates', 'value', 'ASC');
    $result = $query->execute();
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

    $entry->startDate = json_encode(date($format, $adjustedStart));
    $entry->endDate = json_encode(date($format, $adjustedEnd));
    $entry->headline = json_encode($date->title);

    if(isset($date->body['und'][0]['safe_value'])){
      $entry->text = $date->body['und'][0]['safe_value'];
    } else {
      $entry->text = "";
    }
    if(isset($date->field_read_more['und'][0]['value'])){
      $readmore = '<p><a href="'.$date->field_read_more['und'][0]['value'].'" title="Read More">Read More</a></p>';
      $entry->text .= $readmore;
    }
    $entry->text = json_encode($entry->text);

    if(!empty($date->field_timeline_category['und'][0]['tid'])){
      $entry->tag = taxonomy_term_load($date->field_timeline_category['und'][0]['tid'])->name;
      $entry->tag = json_encode($entry->tag);
    }

    $entry->asset = new stdclass();
    if(isset($date->field_media['und'][0]['fid'])){
      $image = file_load($date->field_media['und'][0]['fid']);
      $entry->asset->media = json_encode(file_create_url($image->uri));
      $entry->asset->thumbnail = json_encode(image_style_url('timelinejs_thumb', $image->uri));
    }
    if(isset($date->field_media_url['und'][0]['value'])){
      $entry->asset->media_url = json_encode($date->field_media_url['und'][0]['value']);
    }
    if(isset($date->field_media_caption['und'][0]['value'])){
      $entry->asset->caption = json_encode($date->field_media_caption['und'][0]['value']);
    }
    if(isset($date->field_media_credit['und'][0]['value'])){
      $entry->asset->credit = json_encode($date->field_media_credit['und'][0]['value']);
    }
    if(isset($date->field_custom_class_name['und'][0]['value'])){
      $entry->class = json_encode($date->field_custom_class_name['und'][0]['value']);
    }
    $dateJson .= '{"startDate":' . $entry->startDate .',';
    $dateJson .= '"endDate":' . $entry->endDate .',';
    $dateJson .= '"headline":' . $entry->headline .',';
    $dateJson .= '"text":' . $entry->text ;

    if(isset($entry->tag)){
      $dateJson .= ',"tag":' . $entry->tag;
    }
    if(isset($entry->class)){
      $dateJson .= ',"classname":'.$entry->class;
    }

    if(isset($entry->asset->media)){
      $dateJson .= ',"asset":{';
      $dateJson .= '"media":'.$entry->asset->media;
      $dateJson .= ',"thumbnail":'.$entry->asset->thumbnail;

      if(!isset($entry->asset->caption) && !isset($entry->asset->credit)){
        $dateJson .= '}';
      } elseif(isset($entry->asset->caption)){
          $dateJson .= ',"caption":'.$entry->asset->caption;
          if(!isset($entry->asset->credit)){
            $dateJson .= '}';
          } else {
            $dateJson .= ',"credit":'.$entry->asset->credit.'}';
          }
      } else {
          $dateJson .= ',"credit":'.$entry->asset->credit.'}';
        }
    } elseif(isset($entry->asset->media_url)){
      $dateJson .= ',"asset":{';
      $dateJson .= '"media":'.$entry->asset->media_url;

      if(!isset($entry->asset->caption) && !isset($entry->asset->credit)){
        $dateJson .= '}';
      } elseif(isset($entry->asset->caption)){
          $dateJson .= ',"caption":'.$entry->asset->caption;
          if(!isset($entry->asset->credit)){
            $dateJson .= '}';
          } else {
            $dateJson .= ',"credit":'.$entry->asset->credit.'}';
          }
      } else {
          $dateJson .= ',"credit":'.$entry->asset->credit.'}';
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

  if(isset($block_id_era) && !empty($block_id_era)){
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_era')
      ->entityCondition('entity_id', $block_id_era, 'IN')
      ->fieldOrderBy('field_dates', 'value', 'ASC')
      ->execute();
    if(count($result) > 0){
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
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

      $entry->startDate = json_encode(date($format, $adjustedStart));
      $entry->endDate = json_encode(date($format, $adjustedEnd));

      $entry->headline = json_encode($era->title);
      $entry->text = isset($era->body['und'][0]['safe_value']) ? $era->body['und'][0]['safe_value'] : "";
      $entry->text = json_encode($entry->text);
      if(isset($era->field_timeline_category['und'][0]['tid'])){
        $entry->tag = json_encode(taxonomy_term_load($era->field_timeline_category['und'][0]['tid'])->name);
      }

      $eraJson .= '{"startDate":' . $entry->startDate . ',';
      $eraJson .= '"endDate":' . $entry->endDate .',';
      $eraJson .= '"headline":' . $entry->headline .',';
      $eraJson .= '"text":' . $entry->text;
      if(isset($entry->tag)){
        $eraJson .= ',"tag":' . $entry->tag;
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

function _timelinejs_block_chart_generator($block_id) {
  $block_id_era = variable_get('timelinejs_block_chart_'.$block_id);

  if(isset($block_id_era) && !empty($block_id_era)){
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timelinejs_chart')
      ->entityCondition('entity_id', $block_id_era, 'IN')
      ->fieldOrderBy('field_dates', 'value', 'ASC')
      ->execute();
    if(count($result) > 0){
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
  }

  if(!empty($nodes)){ 
    $chartJson = ',"chart":[';

    $timezone = date_default_timezone();

    foreach($nodes as $chart){
      $entry = new stdClass();
      $startDate = date_create($chart->field_dates['und'][0]['value']);
      $endDate = date_create($chart->field_dates['und'][0]['value2']);

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

      $entry->startDate = json_encode(date($format, $adjustedStart));
      $entry->endDate = json_encode(date($format, $adjustedEnd));

      $entry->headline = json_encode($chart->title);
      $entry->chart_value = json_encode($chart->field_chart_value['und'][0]['value']);

      $chartJson .= '{"startDate":' . $entry->startDate . ',';
      $chartJson .= '"endDate":' . $entry->endDate .',';
      $chartJson .= '"headline":' . $entry->headline .',';
      $chartJson .= '"value":' . $entry->chart_value;

      if($chart === end($nodes)){
        $chartJson .= '}]';
      } else {
        $chartJson .= '},';
      }
    }
    return $chartJson;
  } else {
    return '';
  }
}
