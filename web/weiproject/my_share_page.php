<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';

$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","index.php?page=login");
}
if(!isset($_GET['cou_id'])){
    info_to_user("cou_id参数为空！");
}
$vcode_parm = "";
if(isset($_GET['type'])){
    if($_GET['type'] == "share"){
        $user_id = $_COOKIE['weipro']['id'];
        if(!$control->is_menager($user_id)){
            $share_times = $control->get_share_times($user_id,"user",$_GET['cou_id']);
            if($share_times == 0){
                info_to_user("您的分享次数已经用完啦！");
            }
            if($control->is_disabled($user_id, $_GET['cou_id'])){
                info_to_user("此优惠券已经过期，不可分享！");
            }
        }
        $vcode_parm = "/weipro/show_vcode.php?type=share&cou_id={$_GET['cou_id']}&user_id=$user_id";
        $share_title = $control->get_coupon_title($_GET['cou_id']);
        $temp['page_title'] = "我的分享码";
        $temp['head_title'] = "优惠券分享";
        $temp['note'] = "【优品油购】【{$share_title}】分享给你快去使用吧！将此页面截图发给朋友。";
    }else if($_GET['type'] == "use"){
        $user_id = $_COOKIE['weipro']['id'];
        if($control->is_disabled($user_id,$_GET['cou_id'])){
            info_to_user("此优惠券已过期！");
        }
        if($control->is_used($user_id,$_GET['cou_id'])){
            info_to_user("此优惠券已经使用了！");
        }
        $vcode_parm = "/weipro/show_vcode.php?type=use&cou_id={$_GET['cou_id']}&user_id=$user_id";
        $share_title = $control->get_coupon_title($_GET['cou_id']);
        $temp['page_title'] = "我的分享码";
        $temp['head_title'] = "优惠券使用";
        $temp['note'] = "【优品油购】【{$share_title}】快去门店使用吧！";
    }else{
        info_to_user("type参数有误！");
    }
}else{
    info_to_user("type参数为空！");
}

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title><?php echo $temp['page_title']?></title>
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">

    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm.min.css">
    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm-extend.min.css">

  </head>
  <body>
    <div class="page-group">
        <div class="page page-current">
        <header class="bar bar-nav">
          <h1 class="title"><?php echo $temp['head_title']?></h1>
          <a href="#" class="icon icon-left pull-left back"></a>
        </header>
        <div class="content">
            <div class="card demo-card-header-pic">
                <div valign="bottom" class="card-header color-white no-border no-padding">
                  <img class='card-cover' src="<?php echo $vcode_parm;?>" alt="">
                </div>
                <div class="card-content">
                  <div class="card-content-inner">
                    <p><?php echo $temp['note']?></p>
                    <p class="color-gray">地址：湘乡市湘乡政务优品油购汽车保养中心</p>
                    <p class="color-gray">联系电话：13467936260</p>
                  </div>
                </div>
              </div>
         </div>
        </div>
    </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>

  </body>
</html>