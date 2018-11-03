<?php
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';


$control = new Control();



if(isset($_GET['delete_type'])){
    switch ($_GET['delete_type']){
        case "delete_card":
            if(isset($_GET['cou_id'])){
                if(($id = intval($_GET['cou_id'])) == 0){
                    info_to_user("cou_id参数不合法！");
                }
                $title = "";
                $title = $control->get_coupon_title($id);
                if(empty($title)){
                    info_to_user("cou_id不合法！");
                }
                $url = "/weipro/manage/delete_coupon.php?cou_id=".$id;
                confirm("确定删除（{$title}）？", $url);
            }else{
                info_to_user("cou_id参数为空！");
            }
            break;
        default:info_to_user("delete_type 错误！");
            
    }
}else if(isset($_GET['logout'])){
    
    if(isset($_GET['user_id'])){
        if($control->is_user($_GET['user_id'])){
            if($control->is_login($_GET['user_id'])){
                $url = "/weipro/logout.php?user_id=".$_GET['user_id'];
                confirm("确定退出？", $url);
            }else{
                skip("/weipro/index.php");
            }
        }else{
            info_to_user("您尚未注册，请先注册！","info","注册","/weipro/index.php#register");
        }
    }else{
        info_to_user("user_id参数不合法！");
    }
}

