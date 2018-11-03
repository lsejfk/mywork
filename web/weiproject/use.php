<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';

$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","index.php?page=login");
}else if(!$control->is_menager($_COOKIE['weipro']['id'])){
    info_to_user("您不是管理员，没有权限访问此页面！","info","确定");
}

if(isset($_GET['user_id']) && isset($_GET['cou_id'])){
    $control->use_coupon($_GET['user_id'],$_GET['cou_id']);
}else{
    info_to_user("参数错误！");
}