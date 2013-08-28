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
$css .= '.timenav-tag { background: #558ca1 !Important; }';
$css .= '.vco-navigation .timenav .content .era div {background:transparent !Important; }';
$css .= '.time-interval .era { display: none !Important; }';

echo $css;
