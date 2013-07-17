<?php

header("Content-type: text/css; charset: UTF-8");

$bg_color = isset($_GET['bg']) ? $_GET['bg'] : '#fff';
$font_color = isset($_GET['font']) ? $_GET['font'] : '#333';

echo <<<END
.block-timelinejs-block .nav-next,
.block-timelinejs-block .nav-previous {
  background-color: $bg_color;
  color: $font_color;
}
END;
