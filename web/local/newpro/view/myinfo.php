<?php

include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';


$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","/weipro/index.php?page=login");
}

if(!$control->bandcar($_COOKIE['weipro']['id'])){
    info_to_user("您还未绑定车牌号，请先绑定车牌信息！","info","去绑定","/weipro/manage/add_car.php",true);
}

$show = new InitPage($control,"myinfo.php",false,$_COOKIE['weipro']['id']);

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>个人中心</title>
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
        <!-- 你的html代码 -->
            <header class="bar bar-nav">
              <a href="#" class="icon icon-left pull-left back"></a>
              <h1 class="title">我的信息</h1>
            </header>
            <div class="content">
              <div class="content-block-title">我的车辆信息</div>
              <div class="list-block">
                <ul>
                  <li class="item-content">
                    <div class="item-media"><i class="icon icon-f7"></i></div>
                    <div class="item-inner">
                      <div class="item-title">车牌号</div>
                      <div class="item-after"><?php echo $show->template['car_id']?></div>
                    </div>
                  </li>
                  <li class="item-content">
                    <div class="item-media"><i class="icon icon-f7"></i></div>
                    <div class="item-inner">
                      <div class="item-title">车型</div>
                      <div class="item-after"><?php echo $show->template['car_type']?></div>
                    </div>
                  </li>
                  <li class="item-content">
                    <div class="item-media"><i class="icon icon-f7"></i></div>
                    <div class="item-inner">
                      <div class="item-title">颜色</div>
                      <div class="item-after"><?php echo $show->template['car_color']?></div>
                    </div>
                  </li>
                </ul>
              </div>
              
            </div>
        </div>
    </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>

  </body>
</html>