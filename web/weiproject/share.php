<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
$control = new Control();
$url_my = "";
if(isset($_GET['cou_id']) && isset($_GET['user_id'])){
    //get the share user's share times
    
    //check the user's login status
    if(isset($_COOKIE['weipro']['id']) && $control->is_login($_COOKIE['weipro']['id'])){
        if($control->is_user($_COOKIE['weipro']['id'])){    //have registered
            if($control->is_menager($_GET['user_id'])){
                echo "user_id";
                $share_times = $control->get_share_times($_GET['cou_id']);
            }else{
                if($control->get_share_times($_GET['user_id'],"user",$_GET['cou_id']) == 0){
                    info_to_user("糟糕！来晚一步，已经领完啦！");
                }
                $share_times = 0;
            }
            $control->obtain_cou($_GET['user_id'],$_GET['cou_id'],$_COOKIE['weipro']['id'],$share_times);
        }
    }
    
    if(isset($_POST['submit'])){
        if(isset($_POST['usrid'])){
            if($control->is_user($_POST['usrid'])){    //have registered
                if($control->is_menager($_GET['user_id'])){
                    $share_times = $control->get_share_times($_GET['cou_id']);
                }else{
                    if($control->get_share_times($_GET['user_id'],"user",$_GET['cou_id']) == 0){
                        info_to_user("糟糕！来晚一步，已经领完啦！");
                    }
                    $share_times = 0;
                }
                $control->obtain_cou($_GET['user_id'],$_GET['cou_id'],$_POST['usrid'],$share_times);
            }else{
                $url = $_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
                $url = urlencode($url);
                info_to_user("您还未注册，请先注册！","info","注册","/weipro/index.php?page=register&back={$url}");
            }
        }
    }
    
    $url_my = "?cou_id=".$_GET['cou_id']."&user_id=".$_GET['user_id'];
    $show = new InitPage($control,"oncard",$_GET['cou_id']);
}else{
    info_to_user("参数不合法！");
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
        	<?php for($i=0;$i<$show->get_num_of_template();$i++) {?>
        	<div class="card">
                <div class="card-header">
                <?php echo $show->template[$i]['title']?>
                <a href="#coupon_detail<?php echo $show->template[$i]['cou_id']?>"><span class="icon icon-right"></span></a>
                </div>
                <div class="card-content">
                <div class="card-content-inner"><?php echo $show->template[$i]['intro']?></div>
                </div>
                <div class="card-footer"><?php echo $show->template[$i]['type']?>
                </div>
              </div>
        		<?php }?>

			<form action="/weipro/share.php<?php echo $url_my;?>" method="post">
              <div class="list-block">
                <ul>
                  <!-- Text inputs -->
                  <li>
                    <div class="item-content">
                      <div class="item-media"><i class="icon icon-form-name"></i></div>
                      <div class="item-inner">
                        <div class="item-title label">手机</div>
                        <div class="item-input">
                          <input id="get_user_id" type="text" name="usrid" placeholder="Your phone number">
                        </div>
                      </div>
                    </div>
                  </li>
                </ul>
              </div>
              <div class="content-block">
              	<p><input id="getcoupon_submit" name="submit" type="submit" class="button button-big button-success alert-text" value="领取"/></p>
              </div>
          </form>
        </div>
        </div>
         <?php for($i=0;$i<$show->get_num_of_template();$i++){?>
        <div class="page" id="coupon_detail<?php echo $show->template[$i]['cou_id']?>">
                    <header class="bar bar-nav">
                		<a href="#" class="icon icon-left pull-left back"></a>
                        <h1 class="title">优惠券</h1>
                    </header>
                    
                    <div class="content">
                    	<div class="card">
                        <div class="card-header">详细信息
                        </div>
                        <div class="card-content">
                            <div class="card-content-inner">
                            	<h3>优惠券类型：</h3>
                            	<ul>
                            	<li><?php echo $show->template[$i]['type']?></li>
                                </ul>
                                <h3>有效期：</h3>
                                <ul>
                                <li><?php echo $show->template[$i]['expire_date']?></li>
                                </ul>
                                <h3>优惠券等级：</h3>
                                <ul>
                                <li><?php echo $show->template[$i]['level']?></li>
                                </ul>
                                <h3>分享奖励信息：</h3>
                                <ul>
                                <li><?php echo $show->template[$i]['reward']?></li>
                                </ul>
                                <h3>使用规则：</h3>
                                <ul>
                                <?php foreach ($show->template[$i]['list_detail'] as $val){?>
                                <li><?php echo $val;?></li>
                                <?php }?>
                                </ul>
                            </div>
                        </div>
                    </div> 
                    </div>
                </div>
                <?php }?>
        
    </div>
    

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="myjs/ajax.js"></script>
	<script type="text/javascript" src="myjs/check.js"></script>
  </body>
</html>