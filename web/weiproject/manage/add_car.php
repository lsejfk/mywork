<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';


$control = new Control();

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","/weipro/index.php?page=login");
}
if(isset($_POST['submit'])){
    $control->creat_rec_object($_POST,"add_car.php", "post");
    $control->submit_rec_data($_COOKIE['weipro']['id']);
    $_POST = array();
}
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>绑定车牌</title>
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
          <h1 class='title'>绑定车牌</h1>
        </header>
        <p></p>
        <p></p>
        <form action="add_car.php" enctype="multipart/form-data" method="post">
        <div class="content">
          <div class="list-block">
          
            <ul>
              <!-- Text inputs -->
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">车牌号码</div>
                    <div class="item-input">
                      <input id="input_car_id" type="text" name="car_id" placeholder="粤SU0E46">
                    </div>
                  </div>
                </div>
              </li>
              

              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div id="" class="item-title label">车型</div>
                    <div class="item-input">
                      <input id="input_car_type" name="car_type" type="text" placeholder="比亚迪S7">
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div id="" class="item-title label">车颜色</div>
                    <div class="item-input">
                      <input id="input_car_color" name="car_color" type="text" placeholder="黑色">
                    </div>
                  </div>
                </div>
              </li>

            </ul>
            
          </div>
          <div class="content-block">
            <div class="row">
              <div class="col-50"><a href="/weipro/coupon.php" class="button button-big button-fill button-danger">取消</a></div>
              <div class="col-50"><input id="add_car" name="submit" type="submit" class="button button-big button-fill button-success alert-text" value="提交"></div>
            </div>
            
          </div>
          
        </div>
        </form>
        </div>
    </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="/weipro/myjs/ajax.js"></script>
	<script type="text/javascript" src="/weipro/myjs/check.js"></script>
  </body>
</html>