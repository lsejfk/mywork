<?php
include_once '/var/www/html/weipro/qcode/qrlib.php';

function get_code($info,$size="4",$errorLevel="L"){
    //定义纠错级别
    $errorLevel = "L";
    $size = "4";
    QRcode::png($info, false, $errorLevel, $size);
}