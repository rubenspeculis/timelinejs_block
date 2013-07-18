<?php

header("Content-type: text/css; charset: UTF-8");

foreach($_GET as $key => $color) {
  $values[$key] = $color;
}


$css = '';

if(isset($values)) {
  $css .= 
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-1,'."\n".
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-3,'."\n".
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-5 {background: '. $values['oddcolor'] .';}'."\n";

  $css .=
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-2,'."\n".
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-4,'."\n".
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag-row-6 {background: '. $values['evencolor'] .';}'."\n";

  $css .=
    '.block-timelinejs-block .vco-timeline .vco-navigation .timenav-background .timenav-tag div h3 {color: '. $values['catfontcolor'] .';}';
}

echo $css;
