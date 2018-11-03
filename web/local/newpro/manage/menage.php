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
$show = new InitPage($control,"menage.php");
$timestamp = time();
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>优惠券</title>
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">

    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm.min.css">
    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm-extend.min.css">

  </head>
  <body>
    <div class="page-group">
        <div class="page current-page" id="card_list">
            <header class="bar bar-nav">
                    <h1 class="title">管理优惠券</h1>
                    <a class="icon icon-menu pull-left open-panel" data-panel='#panel-left-demo'></a>
                    <a href="add_coupon.php?time=<?php echo $timestamp;?>" class="icon icon-edit pull-right" data-no-cache="true"></a>
            </header>
            	<div class="content" >
            		
            	<?php 
            	for($i=0;$i<$show->get_num_of_template();$i++){
            	    echo $show->menage_card_list($i);
            	}
            	?>
            </div>
        </div>
        
        <div class="panel-overlay"></div>
        <!-- Left Panel with Reveal effect -->
        <div class="panel panel-left panel-reveal theme-dark" id='panel-left-demo'>
          <div class="content-block">
            <ul>
              <li class="item-content">
              <div class="item-media"><i class="icon icon-f7"></i></div>
                  <a>查看营业状况</a>
              </li>
              <li class="item-content">
              <div class="item-media"><i class="icon icon-f7"></i></div>
                  <a>添加客户信息</a>
              </li>
              <li class="item-content">
              <div class="item-media"><i class="icon icon-f7"></i></div>
                  <a>添加消费项目</a>
              </li>
              <li class="item-content">
              <div class="item-media"><i class="icon icon-f7"></i></div>
                  <a href="/weipro/coupon.php">退出管理员身份</a>
              </li>
              <li class="item-content">
              <div class="item-media"><i class="icon icon-f7"></i></div>
                  <a href="/weipro/view/confirm.php?logout&user_id=<?php echo $_COOKIE['weipro']['id']?>">退出登录</a>
              </li>
              
    		</ul>
          </div>
          <div class="list-block">
          
          </div>
        </div>
        
        
        <?php 
        for($i=0;$i<$show->get_num_of_template();$i++){
            echo $show->menage_coupon_detail($i);
        }
        ?>
        
    </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="/weipro/myjs/ajax.js"></script>
	<script type="text/javascript" src="/weipro/myjs/check.js"></script>
  </body>
</html>