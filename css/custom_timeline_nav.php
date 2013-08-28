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

$css .= '.vco-timeline .vco-navigation .timenav .content .marker.active .flag { background: url(../img/timeline.png) !Important; color: #fff !Important }';
$css .= '.vco-timeline .vco-navigation .timenav .content .marker.active .flag h3 { color: #ccc !Important }';
$css .= '.vco-notouch .vco-navigation .timenav .content .marker .flag { background: url(../img/timeline.png) !Important; color: #fff !Important }';
$css .= '.vco-notouch .vco-navigation .timenav .content .marker .flag h3 { color: #fff !Important }';


$css .= '.era-navigation li { display: inline;  margin-right: 6px;}';
$css .= '.era-nav-label {font-weight: bold;}';
$css .= '.era-nav-link { padding-right: 6px; border-right: 1px solid; }';

$css .= '.era-navigation-class .date { display: none; }';
$css .= '.era-navigation-class h3 { font-size: 3em !Important; }';

$css .= '.slider-item { background: url(../img/environment.jpg) no-repeat left top; margin: 0px -140px !important; padding: 0px 140px !Important; overflow-y: hidden !Important; }';
$css .= '.slider-item .text { background: white; position: absolute; top:0px; right: 60px; height: 100% !important; padding: 20px !Important;overflow-y: auto !Important; width: 30% !Important;}';
$css .= '.slider-item .text .container { display: block !Important; overflow-y: auto; height: 355px !Important; width: 100%; padding-left: 0px !Important; text-align: left !Important; }';
$css .= '.slider-item .text h3 {padding-top: 2px !Important; }';
$css .= '.slider-item .media { width: 40% !Important; }';
$css .= '.slider-item .media img {display:none !Important;}';
$css .= '.slider-item .media .credit {display:none !Important;}';
$css .= '.slider-item .media .caption {display:none !Important;}';

$css .= '.era-navigation-class { background: url(../img/monitoring.jpg) no-repeat left top; }';
$css .= '.era-navigation-class .media-image { display: none !Important; }';
$css .= '.era-navigation-class .text { background: transparent !Important; color: #fff !IMportant; }';
$css .= '.era-navigation-class .text h3 { color: #fff !Important; }';

$css .= '.monitoring { background: url(../img/monitoring.jpg) no-repeat left top; }';
$css .= '.monitoring .media-image { display: none !Important; }';

$css .= '.constraint-prelim{ background: url(../img/constraint-prelim.jpg) no-repeat left top; }';
$css .= '.constraint-prelim .media-image { display: none !Important; }';

$css .= '.constraint{ background: url(../img/constraint-strat.jpg) no-repeat left top; }';
$css .= '.constraint .media-image { display: none !Important; }';

$css .= '.environment{ background: url(../img/environment.jpg) no-repeat left top; }';
$css .= '.environment .media-image { display: none !Important; }';

$css .= '.groundwater{ background: url(../img/groundwater.jpg) no-repeat left top; }';
$css .= '.groundwater .media-image { display: none !Important; }';
echo $css;
