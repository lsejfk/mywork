<?php
var_dump($_SERVER);
exit();
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';

$control = new Control();

if(isset($_GET['cou_id'])){
    $show = new InitPage($control,"oncard",$_GET['cou_id']);
}else{
    info_to_user("cou_id参数为空！");
}


?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>领取优惠券</title>
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">

    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm.min.css">
    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm-extend.min.css">

  </head>
  <body>
  <div class="page-group">
     <div class="page current-page" id="get_coupon">
        <header class="bar bar-nav">
                <h1 class="title">领取优惠券</h1>
        </header>
        
        <div class="content">
        
        		<?php 
            	for($i=0;$i<$show->get_num_of_template();$i++){
            	    echo $show->menage_card_list($i);
            	}
            	?>

			<form action="getcoupon.php" method="post">
              <div class="list-block">
                <ul>
                  <!-- Text inputs -->
                  <li>
                    <div class="item-content">
                      <div class="item-media"><i class="icon icon-form-name"></i></div>
                      <div class="item-inner">
                        <div class="item-title label">手机</div>
                        <div class="item-input">
                          <input id="get_user_id" type="text" name="user_id" placeholder="Your phone number">
                        </div>
                      </div>
                    </div>
                  </li>
                </ul>
              </div>
              <div class="content-block">
              	<p><input id="getcoupon_submit" name="login" type="submit" class="button button-big button-success alert-text" value="领取"/></p>
              </div>
          </form>
        </div>
        
         <?php 
        for($i=0;$i<$show->get_num_of_template();$i++){
            echo $show->menage_coupon_detail($i);
        }
        ?>
        
        
    </div>
    
</div>
    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="myjs/ajax.js"></script>
	<script type="text/javascript" src="myjs/check.js"></script>
  </body>
</html>