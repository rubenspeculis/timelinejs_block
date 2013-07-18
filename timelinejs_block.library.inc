<?php

/**
 * @file
 * Implements libraries hooks and requirements hook for TimelineJS.
 */

/**
 * Implement hook_libraries_info().
 */
function timelinejs_block_libraries_info() {
  $libraries['TimelineJS'] = array(
    'name' => 'TimelineJS',
    'vendor url' => 'http://timeline.verite.co/',
    'download url' => 'https://github.com/VeriteCo/TimelineJS',
    'version arguments' => array(
      'file' => 'compiled/js/timeline.js',
      'pattern' => '/Version (\d.\d+)/',
      'lines' => 50,
    ),
    'path' => 'compiled',
    'files' => array(
      'js' => array(
        'js/timeline.js',
        'js/storyjs-embed.js'
      ),
      'css' => array(
        'css/timeline.css'
      )
    )
  );
  return $libraries;
}

/**
 * Implements hook_requirements().
 */
function timelinejs_block_requirements($phase){
  $name = 'TimelineJS';
  if($phase === 'runtime'){
    if(($library = libraries_load($name)) && !empty($library['loaded'])){
      $requirements['timelinejs_block_req'] = array(
        'title' => 'TimelineJS Library',
        'value' => 'All is well and the Library is correctly installed',
        'serverity' => REQUIREMENT_INFO,
      );
    } else {
      $error = ($library['error message']);
      $requirements['timelinejs_block_req'] = array(
        'title' => 'TimelineJS Library',
        'value' => $error ,
        'serverity' => REQUIREMENT_INFO,
      );
    }
  }
  return $requirements;
}
