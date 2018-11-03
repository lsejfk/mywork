<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';

$control = new Control();

if(isset($_GET['user_id'])){
    $control->logout($_GET['user_id']);
}else{
    info_to_user("user_id参数错误！");
}