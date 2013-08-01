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


$css .= '.era-navigation li { display: inline;  margin-right: 6px;}';
$css .= '.era-nav-label {font-weight: bold;}';
$css .= '.era-nav-link { padding-right: 6px; border-right: 1px solid; }';

$css .= '.era-navigation-class .date { display: none; }';
$css .= '.era-navigation-class h3 { font-size: 3em !Important; }';

echo $css;
