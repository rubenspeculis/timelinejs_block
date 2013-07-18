<?php

header("Content-type: text/css; charset: UTF-8");

foreach($_GET as $key => $color) {
  $era[$key] = $color;
}


$css = '';

if(isset($era)) {
  foreach($era as $class => $color) {
    $css .= '.block-timelinejs-block .' . $class . ' { color: ' . $color . ' !Important; }'."\n";
    $css .= '.block-timelinejs-block .' . $class . ' div { background: ' . $color . ' !Important; }'."\n";
  }
}

echo $css;
