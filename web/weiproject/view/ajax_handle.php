<?php
include_once '/var/www/html/weipro/controler/control.class.php';
include_once '/var/www/html/weipro/view/init_page.class.php';
/*
*Created by Michael Shen
*Date:2018-09-10
*Time:19:00
*Dec:handle ajax request
*/

function show_full_sub(){
    $html = <<<A
<div class="item-content">
  <div class="item-media"><i class="icon icon-form-name"></i></div>
  <div class="item-inner">
    <div class="item-title label">优惠金额</div>
    <div class="item-input">
      <input type="text" name="coupon_money" placeholder="Your coupon">
    </div>
  </div>
</div>

A;
return $html;
}


function show_time_calendar(){
    $html = <<<A
<div class="item-content">
  <div class="item-media"><i class="icon icon-form-calendar"></i></div>
  <div class="item-inner">
    <div class="item-title label">截止日期</div>
    <div class="item-input">
      <input type="date" name="calendertime" placeholder="Deadtime" value="2014-04-30">
    </div>
  </div>
</div>
A;
return $html;
}

function show_cou_list(){
    $control = new Control();
    $show = new InitPage($control, "add_coupon.php");
    $option = $show->show_coupon_list();
    $html = <<<A
      <div class="item-content">
          <div class="item-media"><i class="icon icon-form-gender"></i></div>
          <div class="item-inner">
            <div class="item-title label">选择奖励的优惠券</div>
            <div class="item-input">
              <select id="" name="" onchange="">
                {$option}
              </select>
            </div>
          </div>
        </div>
A;
    return $html;
}

function show_other(){
    $html = <<<A
        <div class="item-content">
          <div class="item-media"><i class="icon icon-form-comment"></i></div>
          <div class="item-inner">
            <div class="item-title label">其它奖励措施</div>
            <div class="item-input">
              <textarea id="textarea_other_reward" name="other_reward" placeholder="请输入其它奖励策略"></textarea>
            </div>
          </div>
        </div>
A;
    return $html;
}

function show_time_days(){
    $html = <<<A
<div class="item-content">
  <div class="item-media"><i class="icon icon-form-name"></i></div>
  <div class="item-inner">
    <div class="item-title label">有效期</div>
    <div class="item-input">
      <input  id="add_input_days" name="days" type="text" placeholder="输入有效天数">
    </div>
  </div>
</div>
A;
return $html;
}

function show_share_record($share_id){
    $control = new Control();
    $record = $control->get_share_record($share_id);
    if($record['status'] == 1){
        $title = $control->get_coupon_title($record['cou_id']);
        $info = "已经成功分享给【{$record['to_user_id']}】，并获得【{$title}】奖励，您可以在首页查看！";
    }else{
        $info = "已经成功分享给【{$record['to_user_id']}】，但对方还未使用此优惠券，奖励还未到帐！";
    }
    $html = <<<A
        <div class="card-content">
            <div class="card-content-inner">
                <h4>详情：</h3>
                <ul>
                    <li>时间：{$record['share_time']}</li>
                    <li>状态：{$info}</li>
                </ul>
            </div>
        </div>
A;
    return $html;
}

if(isset($_GET['type'])){
    switch ($_GET['type']){
        //满减
        case "full_subtra" :
            echo show_full_sub();
            break;
        //截止日期
        case "time_calender":
            echo show_time_calendar();
            break;
        case "time_days":
            echo show_time_days();
            break;
        case "reward_cou":
            echo show_cou_list();
            break;
        case "other_list":
            echo show_other();
            break;
        case "share_record":
            echo show_share_record($_GET['share_id']);
            break;
        case "remove_badg" :
            echo "";
            break;
    }
}