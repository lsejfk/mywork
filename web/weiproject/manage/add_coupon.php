<?php 
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';



/*Created by Michael Shen
 *Date:2018-09-09
 *Time:10:15
 *Dec:receive data from the html and do actions to mysql
 */


$control = new Control();
$show = new InitPage($control, "add_coupon.php");

if(!isset($_COOKIE['weipro']['id']) || !$control->is_login($_COOKIE['weipro']['id'])){
    info_to_user("您未登录","info","确定","/weipro/index.php?page=login");
}else if(!$control->is_menager($_COOKIE['weipro']['id'])){
    info_to_user("您不是管理员，没有权限访问此页面！","info","确定");
}

if(isset($_POST['submit'])){
    $control->creat_rec_object($_POST,"add_coupon.php", "post");
    $control->submit_rec_data();
    $_POST = array();
}

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>添加优惠券</title>
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
          <h1 class='title'>添加</h1>
        </header>
        <p></p>
        <form action="add_coupon.php" enctype="multipart/form-data" method="post">
        <div class="content">
        
          <div class="list-block">
          
            <ul>
              <!-- Text inputs -->
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">标题</div>
                    <div class="item-input">
                      <input id="add_coupon_title" type="text" name="title" placeholder="Your title">
                    </div>
                  </div>
                </div>
              </li>
              
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">优惠类型</div>
                    <div class="item-input">
                      <select id="add_select_coupon_type" name="coupon_type" onchange="show_coupon_type(this.value)">
                        <option value="1">满减</option>
                        <option value="2">折扣</option>
                        <option value="4">现金代金券</option>
                      </select>
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">时间类型</div>
                    <div class="item-input">
                      <select id="add_select_time_type" name="time_type" onchange="show_time_list(this.value)">
                        <option value="128">固定日期截止</option>
                        <option value="64">有效天数</option>
                      </select>
                    </div>
                  </div>
                </div>
              </li>
              <!-- Date -->
              
              <li id="li_time_type">
              	<div class="item-content">
                  <div class="item-media"><i class="icon icon-form-calendar"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">截止日期</div>
                    <div class="item-input">
                      <input id="add_input_calender" type="date" name="calendertime" placeholder="Deadtime" value="2014-04-30">
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div id="div_label_money" class="item-title label">基础金额</div>
                    <div class="item-input">
                      <input id="input_money" name="basemoney" type="text" placeholder="base">
                    </div>
                  </div>
                </div>
              </li>
              
              <li id="full_subtra_ajax">
             	 <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">优惠金额</div>
                    <div class="item-input">
                      <input id="add_input_coupon_money" type="text" name="coupon_money" placeholder="Your coupon">
                    </div>
                  </div>
                </div>
              </li>
              
              <li id="">
             	 <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-name"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">可分享的次数</div>
                    <div class="item-input">
                      <input id="add_share_times" type="text" name="share_times" placeholder="times">
                    </div>
                  </div>
                </div>
              </li>
              
               <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">优惠等级</div>
                    <div class="item-input">
                      <select id="" name="cou_level" onchange="">
                      	<option value="0">限量优惠券（只能分享）</option>
                        <option value="1">普通优惠券</option>
                        <option value="2">白银优惠券</option>
                        <option value="3">黄金优惠券</option>
                      </select>
                    </div>
                  </div>
                </div>
              </li>
              
              <li>
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">分享奖励类型</div>
                    <div class="item-input">
                      <select id="share_reward_type" name="reward_type" onchange="show_reward_list(this.value)">
                        <option value="1">优惠券</option>
                        <option value="2">其它</option>
                        <option value="3">无</option>
                      </select>
                    </div>
                  </div>
                </div>
              </li>
              
              <li id="reward_cou_list">
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-gender"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">选择奖励的优惠券</div>
                    <div class="item-input">
                      <select id="reward_coupon_id" name="reward_coupon" >
                      	<?php echo $show->show_coupon_list();?>
                      </select>
                    </div>
                  </div>
                </div>
              </li>
              
              <li id="other_reward_list"></li>
              
              <li class="align-top">
                <div class="item-content">
                  <div class="item-media"><i class="icon icon-form-comment"></i></div>
                  <div class="item-inner">
                    <div class="item-title label">详细信息</div>
                    <div class="item-input">
                      <textarea id="textarea_detail" name="detail" placeholder="请输入详细使用规则，每条规则占一行"></textarea>
                    </div>
                  </div>
                </div>
              </li>
              
              
            </ul>
            
          </div>
          <div class="content-block">
            <div class="row">
              <div class="col-50"><a href="#" class="button button-big button-fill button-danger back">取消</a></div>
              <div class="col-50"><input id="add_submit" name="submit" type="submit" class="button button-big button-fill button-success alert-text" value="提交"></div>
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