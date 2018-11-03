<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';

$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","/weipro/index.php?page=login");
}else if(!$control->is_menager($_COOKIE['weipro']['id'])){
    info_to_user("您不是管理员，没有权限访问此页面！","info","确定");
}

if(isset($_GET['cou_id'])){
    if(($cou_id = intval($_GET['cou_id'])) == 0){
        info_to_user("参数不合法！");
    }
    if($control->delete_coupon($cou_id)){
        info_to_user("删除成功！","success","确定","menage.php",true);
    }else{
        info_to_user("删除失败！","info","返回");
    }
}else{
    info_to_user("参数为空！");
}