<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
$control = new Control();

$control->obtain_cou('13469852365',9,'15823654895',9);
exit();
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>我的生活</title>
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
          <h1 class="title">优惠券分享</h1>
        </header>
        <div class="content">
            <div class="card demo-card-header-pic">
                <div valign="bottom" class="card-header color-white no-border no-padding">
                  <img class='card-cover' src="show_vcode.php" alt="">
                </div>
                <div class="card-content">
                  <div class="card-content-inner">
                    <p>【店名】【5元洗车券！】分享给你快去使用吧！</p>
                    <p class="color-gray">地址：湘乡市东山学校</p>
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