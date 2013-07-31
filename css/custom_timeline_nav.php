<?php

header("Content-type: text/css; charset: UTF-8");

$css = '
  .block-timelinejs-block .vco-timeline .vco-navigation .timenav .time .time-interval div:not(.era) {
    font-size: 16px; !Important;
    text-indent: -17px !Important;
  }';

$css .= '
  .block-timelinejs-block .vco-timeline .vco-navigation .timenav .time .time-interval-major div {
    font-size: 18px !Important;
    text-indent: -20px !Important;
  }';

echo $css;
