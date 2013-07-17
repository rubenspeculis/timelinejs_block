<?php
header("Content-type: text/css; charset: UTF-8");

$font_family1 = $_GET['font1'];
$font_family2 = $_GET['font2'];

$font_css = "
  .block-timelinejs-block .vco-storyjs p,
  .block-timelinejs-block .vco-storyjs blockquote,
  .block-timelinejs-block .vco-storyjs blockquote p,
  .block-timelinejs-block .vco-storyjs .twitter blockquote p {
    font-family:'$font_family2',serif !Important;
  }
  .block-timelinejs-block .timeline-tooltip {
    font-family:'$font_family1',sans-serif !Important;
  }
  .block-timelinejs-block .vco-storyjs,
  .block-timelinejs-block .vco-storyjs .vco-feature h1,
  .block-timelinejs-block .vco-storyjs .vco-feature h2,
  .block-timelinejs-block .vco-storyjs .vco-feature h3,
  .block-timelinejs-block .vco-storyjs .vco-feature h4,
  .block-timelinejs-block .vco-storyjs .vco-feature h5,
  .block-timelinejs-block .vco-storyjs .vco-feature h6 {
    font-family:'$font_family2',serif !Important;
  }

  .block-timelinejs-block .vco-storyjs .twitter,
  .block-timelinejs-block .vco-storyjs .vcard,
  .block-timelinejs-block .vco-storyjs .messege,
  .block-timelinejs-block .vco-storyjs .credit,
  .block-timelinejs-block .vco-storyjs .caption,
  .block-timelinejs-block .vco-storyjs .zoom-in,
  .block-timelinejs-block .vco-storyjs .zoom-out,
  .block-timelinejs-block .vco-storyjs .back-home,
  .block-timelinejs-block .vco-storyjs .time-interval div,
  .block-timelinejs-block .vco-storyjs .time-interval-major div,
  .block-timelinejs-block .vco-storyjs .nav-container,
  .block-timelinejs-block .vco-storyjs .vco-feature h1.date,
  .block-timelinejs-block .vco-storyjs .vco-feature h2.date,
  .block-timelinejs-block .vco-storyjs .vco-feature h3.date,
  .block-timelinejs-block .vco-storyjs .vco-feature h4.date,
  .block-timelinejs-block .vco-storyjs .vco-feature h5.date,
  .block-timelinejs-block .vco-storyjs .vco-feature h6.date,
  .block-timelinejs-block .vco-storyjs .timenav h1,
  .block-timelinejs-block .vco-storyjs .flag-content h1,
  .block-timelinejs-block .vco-storyjs .era h1,
  .block-timelinejs-block .vco-storyjs .timenav h2,
  .block-timelinejs-block .vco-storyjs .flag-content h2,
  .block-timelinejs-block .vco-storyjs .era h2,
  .block-timelinejs-block .vco-storyjs .timenav h3,
  .block-timelinejs-block .vco-storyjs .flag-content h3,
  .block-timelinejs-block .vco-storyjs .era h3,
  .block-timelinejs-block .vco-storyjs .timenav h4,
  .block-timelinejs-block  .vco-storyjs .flag-content h4,
  .block-timelinejs-block  .vco-storyjs .era h4,
  .block-timelinejs-block  .vco-storyjs .timenav h5,
  .block-timelinejs-block  .vco-storyjs .flag-content h5,
  .block-timelinejs-block  .vco-storyjs .era h5,
  .block-timelinejs-block  .vco-storyjs .timenav h6,
  .block-timelinejs-block  .vco-storyjs .flag-content h6,
  .block-timelinejs-block  .vco-storyjs .era h6 {
    font-family:'$font_family1',sans-serif !Important;
  }";

echo $font_css;
