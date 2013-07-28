<?php

header("Content-type: text/css; charset: UTF-8");

foreach($_GET as $key => $color) {
  $values[$key] = $color;
}


$css = '';

if(isset($values)) {
  if(isset($values['oddcolor'])){
    $css .= 
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-1,'."\n".
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-3,'."\n".
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-5 {background: '. $values['oddcolor'] .';}'."\n";
  }
  if(isset($values['evencolor'])){
    $css .=
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-2,'."\n".
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-4,'."\n".
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-6 {background: '. $values['evencolor'] .';}'."\n";
  }

  if(isset($values['catfontcolor'])){
    $css .=
      '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag div h3 {color: '. $values['catfontcolor'] .';}'."\n";
  }
  if(isset($values['catDisplay']) && $values['catDisplay'] == 'hide'){
    $css .= '.timenav-tag h3 { display: none !Important; }'."\n";
    $css .= '.slide-tag { display: none; }'."\n";
  }
}

echo $css;
