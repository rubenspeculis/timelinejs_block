<?php

header("Content-type: text/css; charset: UTF-8");

foreach($_GET as $key => $color) {
  $era[$key] = $color;
}


$css = '';

if(isset($era)) {
//  foreach($era as $class => $color) {
//    $css .= '.block-timelinejs-block .' . $class . ' { color: ' . $color . ' !Important; }'."\n";
//    $css .= '.block-timelinejs-block .' . $class . ' div { background: ' . $color . ' !Important;';
//    $css .= 'filter: alpha(opacity=30) !Important; khtml-opacity: 0.3 !Important; opacity: 0.3 !Important}'."\n";
//  }
}

$css .= '.timenav-tag { background: #558ca1 !Important; }';
$css .= '.vco-timeline .vco-navigation .timenav-background .timenav-tag-row-1, .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-3, .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-5, .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-2, .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-4, .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-6 { background: #558ca1 !Important; }';
$css .= '.vco-navigation .timenav .content .era div {background:transparent !Important; }';
$css .= '.time-interval .era { display: none !Important; }';

$css .= '.slider-container-mask { height: 364px !Important; }';

echo $css;
