<?php

header("Content-type: text/css; charset: UTF-8");

foreach($_GET as $key => $color) {
  $era[$key] = $color;
}


$css = '';

if(isset($era)) {
  foreach($era as $class => $color) {
    $css .= '.block-timelinejs-block .' . $class . ' { color: ' . $color . ' !Important; }'."\n";
    $css .= '.block-timelinejs-block .' . $class . ' div { background: ' . $color . ' !Important;';
    $css .= 'filter: alpha(opacity=30) !Important; khtml-opacity: 0.3 !Important; opacity: 0.3 !Important}'."\n";
  }
}

$css .= '.era-navigation li { display: inline;  margin-right: 6px;}';
$css .= '.era-nav-label {font-weight: bold;}';
$css .= '.era-nav-link { padding-right: 6px; border-right: 1px solid; }';

$css .= '.era-navigation-class .date { display: none; }';
$css .= '.era-navigation-class h3 { font-size: 3em !Important; }';

echo $css;
