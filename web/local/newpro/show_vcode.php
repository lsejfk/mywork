<?php
require '/var/www/html/weipro/tools/qcode.inc.php';

if(isset($_GET['type']) && isset($_GET['cou_id']) && isset($_GET['user_id'])){
    if($_GET['type'] == "share"){
        $url = "http://youpinyougou.club/weipro/share.php?cou_id=".$_GET['cou_id']."&user_id=".$_GET['user_id'];
    }else if($_GET['type'] == "use"){
        $url = "http://youpinyougou.club/weipro/use.php?cou_id=".$_GET['cou_id']."&user_id=".$_GET['user_id'];
    }
        get_code($url);
}else{
    info_to_user("缺少参数！");
}

