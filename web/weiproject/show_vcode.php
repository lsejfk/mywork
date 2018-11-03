<?php
require '/var/www/html/weipro/tools/qcode.inc.php';

if(isset($_GET['type']) && isset($_GET['cou_id']) && isset($_GET['user_id'])){
    if($_GET['type'] == "share"){
        $url = "http://119.27.190.49/weipro/share.php?cou_id=".$_GET['cou_id']."&user_id=".$_GET['user_id'];
    }else if($_GET['type'] == "use"){
        $url = "http://119.27.190.49/weipro/use.php?cou_id=".$_GET['cou_id']."&user_id=".$_GET['user_id'];
    }
        get_code($url);
}else{
    info_to_user("缺少参数！");
}

