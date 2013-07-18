<?php
/**
 * @file
 * timelinejs_content_types.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function timelinejs_content_types_image_default_styles() {
  $styles = array();

  // Exported image style: timelinejs_thumb.
  $styles['timelinejs_thumb'] = array(
    'name' => 'timelinejs_thumb',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 32,
          'height' => 32,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function timelinejs_content_types_node_info() {
  $items = array(
    'timelinejs_dates' => array(
      'name' => t('TimelineJS Dates'),
      'base' => 'node_content',
      'description' => t('Nodes for dates in TimelineJS'),
      'has_title' => '1',
      'title_label' => t('Headline'),
      'help' => '',
    ),
    'timelinejs_era' => array(
      'name' => t('TimelineJS Era'),
      'base' => 'node_content',
      'description' => t('Eras for TimelineJS'),
      'has_title' => '1',
      'title_label' => t('Headline'),
      'help' => '',
    ),
  );
  return $items;
}
