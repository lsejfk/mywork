<?php

include_once '/var/www/html/weipro/tools/config.inc.php';
require_once '/var/www/html/weipro/tools/tools.inc.php';
require_once '/var/www/html/weipro/view/login.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
include_once '/var/www/html/weipro/controler/control.class.php';

$control = new Control();

if(isset($_COOKIE['weipro']['id']) && $control->is_login($_COOKIE['weipro']['id'])){
    if($control->is_menager($_COOKIE['weipro']['id'])){
        skip("/weipro/manage/menage.php");
    }else{
        skip("/weipro/coupon.php");
    }
}
$template['login'] = "page-current";    //default page

if(isset($_GET['page'])){
    if($_GET['page'] == "login"){
        $template['login'] = "page-current";
        $template['register'] = "";
        $template['title'] = "登录";
    }else if($_GET['page'] == "register"){
        $template['register'] = "page-current";
        $template['login'] = "";
        $template['title'] = "注册";
    }
}

if(isset($_POST['login']) || isset($_POST['register'])){
    if(isset($_GET['back'])){
        $login = new Login(urldecode($_GET['back']));       //get data from form and login in
    }else{
        $login = new Login();
    }
    
}

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title><?php echo $template['title'];?></title>
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black">

    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm.min.css">
    <link rel="stylesheet" href="//g.alicdn.com/msui/sm/0.6.2/css/sm-extend.min.css">

  </head>
  <body>
    <div class="page-group">
     <div class="page <?php echo $template['login'];?>" id="login">
        <header class="bar bar-nav">
                <h1 class="title">登录</h1>
        </header>
        
        <div class="content">
			<form action="index.php" method="post">
              <div class="list-block">
                <ul>
                  <!-- Text inputs -->
                  <li>
                    <div class="item-content">
                      <div class="item-media"><i class="icon icon-form-name"></i></div>
                      <div class="item-inner">
                        <div class="item-title label">手机</div>
                        <div class="item-input">
                          <input id="login_user_id" type="text" name="user_id" placeholder="Your phone number">
                        </div>
                      </div>
                    </div>
                  </li>
                  
                  <li>
                    <div class="item-content">
                      <div class="item-media"><i class="icon icon-form-password"></i></div>
                      <div class="item-inner">
                        <div class="item-title label">密码</div>
                        <div class="item-input">
                          <input id="login_user_psw" type="password" name="user_psw" placeholder="Password" class="">
                        </div>
                      </div>
                    </div>
                  </li>
                </ul>
              </div>
          <div class="content-block">
          	<p><input id="mylogin" name="login" type="submit" data-no-cache="true" class="button button-big button-success alert-text" value="登录"/></p>
          	<p><a href="#register" data-no-cache="true" class="button button-big button-light">注册</a></p>
          </div>
          </form>
        </div>
    </div>
    
    
    <div class="page <?php echo $template['register'];?>" id="register">
        <header class="bar bar-nav">
                <h1 class="title">注册</h1>
        </header>
        <div class="content">
        <form action="index.php" method="post">
          <div class="list-block">
            <ul>
              <!-- Text inputs -->
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">手机</div>
                    <div class="item-input">
                      <input id="register_user_id" type="text" name="user_id" placeholder="Your phone number" />
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">验证码</div>
                    <div class="item-input">
                     	<div class="row">
                          <div class="col-50"><input id="user_yzcode" type="text" name="yzcode" placeholder="number"></div>
                          <div class="col-50"><a id="yzm" onclick="yzm_action()" class="button pull-right" >获取验证码</a></div>
                        </div>
                 
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-password"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">密码</div>
                    <div class="item-input">
                      <input id="register_user_psw" type="password"  name="user_psw" placeholder="Password" />
                    </div>
                  </div>
                </div>
              </li>
              
               <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-password"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">确认密码</div>
                    <div class="item-input">
                      <input id="register_user_psw1" type="password"  name="user_psw1" placeholder="Password" />
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">性别</div>
                    <div class="item-input">
                      <select name="gender">
                        <option value="m">Male</option>
                        <option value="f">Female</option>
                      </select>
                    </div>
                  </div>
                </div>
              </li>

            </ul>
          </div>
          <div class="content-block">
          	<p><input id="myregister" name="register" data-no-cache="true" type="submit" class="button button-big button-light alert-text" value="注册"/></p>
          </div>
          </form>
        </div>
    </div>
    
   </div>

    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
	<script type="text/javascript" src="myjs/ajax.js"></script>
	<script type="text/javascript" src="myjs/check.js"></script>
  </body>
</html>