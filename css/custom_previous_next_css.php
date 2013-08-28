<?php

header("Content-type: text/css; charset: UTF-8");

$bg_color = isset($_GET['bg']) ? $_GET['bg'] : '#fff';
$font_color = isset($_GET['font']) ? $_GET['font'] : '#333';

$bg_color = 'rgba(35,35,45,0.5)';
$font_color = 'rgba(35,35,35,0.7)';

echo <<<END
.block-timelinejs-block .nav-next,
.block-timelinejs-block .nav-previous {
  background-color: $bg_color;
  color: $bg_color !Important;
  height: 90px !Important;
  top: 130px !Important;
  width: 30px !Important;
}

.block-timelinejs-block .nav-next {
  left: 1150px !Important;
}

.block-timelinejs-block .nav-next .nav-container,
.block-timelinejs-block .nav-previous .nav-container {
  top: 23px !Important;
}

.block-timelinejs-block .nav-next .icon {
  background: url(../img/r-arrow_navigation.png) no-repeat !important;
  margin-left: 8px !Important;
}
.block-timelinejs-block .nav-previous .icon {
  background: url(../img/l-arrow_navigation.png) no-repeat !Important;
  margin-left: 8px !Important;
}

.block-timelinejs-block .nav-next:hover,
.block-timelinejs-block .nav-previous:hover {
  color: $font_color !Important;
}

.block-timelinejs-block .nav-next .date,
.block-timelinejs-block .nav-next .title,
.block-timelinejs-block .nav-previous .date,
.block-timelinejs-block .nav-previous .title {
  display: none !Important;
}

END;
