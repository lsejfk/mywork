<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';

$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","index.php?page=login");
}

$show = new InitPage($control,"share_record",$_COOKIE['weipro']['id']);
$records = $control->get_num_of_share_records($_COOKIE['weipro']['id']);
$_COOKIE['today_news']['share_record'] = $records;
$newrecode = 0;
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>分享记录</title>
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">

    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm.min.css">
    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm-extend.min.css">

  </head>
  <body>
    <div class="page-group">
       <div class="page" id="my_record">
        <header class="bar bar-nav">
                <h1 class="title">分享记录</h1>
        </header>
        <nav class="bar bar-tab">
          <a class="tab-item external" href="/weipro/coupon.php?badg=false">
            <span class="icon icon-home"></span>
            <span class="tab-label">我的优惠券</span>
          </a>
          <a class="tab-item external active"  href="#">
            <span class="icon icon-friends"></span>
            <span class="tab-label">分享记录</span>
          </a>
          <a class="tab-item external" href="/weipro/view/myinfo.php">
                <span class="icon icon-me"></span>
                <span class="tab-label">个人中心</span>
         </a>
        </nav>
        	<div class="content">
        	<?php 
        	if($show->get_num_of_template() == 0){
        	    echo '<p style="text-align:center">您还没有分享记录哦，赶快去分享吧！</p>';
        	}
        	?>
            	<div class="list-block">
                    <ul>
                      <?php 
                          if($show->get_num_of_template() > 0){
                            echo $show->show_share_record();
                           }
                       ?>
                    </ul>
                  </div>
                </div>
        	
        	</div>
        </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="/weipro/myjs/ajax.js"></script>
	<script type="text/javascript" src="/weipro/myjs/check.js"></script>
  </body>
</html>
