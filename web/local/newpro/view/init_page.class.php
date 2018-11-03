<?php
/*
*Created by Michael Shen
*Date:2018-09-09
*Time:14:04
*Dec:initialize the page information
*/

include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';


class InitPage{
    public $template;
    private $control;
    public $mylist;
    
    
    public function __construct($control,$page,$id=null,$user_id=null){
        $this->control = $control;
        switch($page){
            case "menage.php":
                $this->template = $this->control->init_menage_page("home");
                break;
            case "coupon.php":
                $this->template['unuse'] = $this->control->init_menage_page("myunuse",false,$user_id);
                $this->template['used'] = $this->control->init_menage_page("myused",false,$user_id);
                $this->template['disabled'] = $this->control->init_menage_page("mydisabled",false,$user_id);
                break;
            case "add_coupon.php":
                $this->template = $this->control->init_add_page();
                break;
            case "oncard":
                $this->template = $this->control->init_menage_page("specify",$id);
                break;
            case "share_record":
                $this->template = $this->control->get_share_info($id);
                break;
            case "myinfo.php":
                $this->template = $this->control->get_car_info($user_id);
                break;
        }
    }
    
    
    public function get_num_of_template($type=null){
        if(isset($type)){
            return count($this->template[$type]);
        }
        return count($this->template);
    }
    public function get_num_of_mylist(){
        return count($this->mylist);
    }
    public function menage_card_list($key){
        $html = <<<A
        
            <div class="card">
                <div class="card-header">
                {$this->template[$key]['title']}
                <a href="#coupon_detail{$this->template[$key]['cou_id']}" data-no-cache="true"><span class="icon icon-right"></span></a>
                </div>
                <div class="card-content">
                <div class="card-content-inner">{$this->template[$key]['intro']}</div>
                </div>
                <div class="card-footer">{$this->template[$key]['type']}【{$this->template[$key]['status']}】
                <a href="/weipro/view/confirm.php?delete_type=delete_card&cou_id={$this->template[$key]['cou_id']}" class="icon icon-remove"></a>
                </div>
              </div>
        
A;
        return $html;
    }
    
    public function menage_coupon_detail($key,$type=null){
        if(isset($type)){
            $html = "";
            
            foreach ($this->template as $keyvalue=>$thevalue){
                for($key=0;$key<count($thevalue);$key++){
                    $html .= <<<A
                    <div class="page" id="coupon_detail{$thevalue[$key]['cou_id']}">
                            <header class="bar bar-nav">
                        		<a href="#" class="icon icon-left pull-left back"></a>
                                <h1 class="title">优惠券</h1>
                            </header>
                            
                            <div class="content">
                            	<div class="card">
                                <div class="card-header">详细信息
                                <a href="/weipro/my_share_page.php?type=share&cou_id={$thevalue[$key]['cou_id']}" class="icon icon-share pull-right"></a>
                                </div>
                                <div class="card-content">
                                    <div class="card-content-inner">
                                    	<h3>优惠券类型：</h3>
                                    	<ul>
                                    	<li>{$thevalue[$key]['type']}</li>
                                        </ul>
                                        <h3>有效期：</h3>
                                        <ul>
                                        <li>{$thevalue[$key]['expire_date']}</li>
                                        </ul>
                                        <h3>优惠券等级：</h3>
                                        <ul>
                                        <li>{$thevalue[$key]['level']}</li>
                                        </ul>
                                        <h3>分享奖励信息：</h3>
                                        <ul>
                                        <li>{$thevalue[$key]['reward']}</li>
                                        </ul>
                                        <h3>使用规则：</h3>
                                        <ul>
A;
                    foreach ($thevalue[$key]['list_detail'] as $val){
                        if(!empty($val)){
                            $html .= "<li>$val</li>";
                        }
                    }
                    $foot = <<<A
                            </ul>
                        </div>
                    </div>
                </div>
                </div>
            </div>
A;
                $html = $html.$foot;
                }//for
            }//foreach
            echo $html;
        }else{
            $html = <<<A
            <div class="page" id="coupon_detail{$this->template[$key]['cou_id']}">
                    <header class="bar bar-nav">
                		<a href="#" class="icon icon-left pull-left back"></a>
                        <h1 class="title">优惠券</h1>
                    </header>
                    
                    <div class="content">
                    	<div class="card">
                        <div class="card-header">详细信息
                            <a href="/weipro/my_share_page.php?type=share&cou_id={$this->template[$key]['cou_id']}" class="icon icon-share pull-right"></a>
                        </div>
                        <div class="card-content">
                            <div class="card-content-inner">
                            	<h3>优惠券类型：</h3>
                            	<ul>
                            	<li>{$this->template[$key]['type']}</li>
                                </ul>
                                <h3>有效期：</h3>
                                <ul>
                                <li>{$this->template[$key]['expire_date']}</li>
                                </ul>
                                <h3>优惠券等级：</h3>
                                <ul>
                                <li>{$this->template[$key]['level']}</li>
                                </ul>
                                <h3>分享奖励信息：</h3>
                                <ul>
                                <li>{$this->template[$key]['reward']}</li>
                                </ul>
                                <h3>使用规则：</h3>
                                <ul>
A;
            foreach ($this->template[$key]['list_detail'] as $val){
                if(!empty($val)){
                    $html .= "<li>$val</li>";
                }
            }
            $foot = <<<A
                                </ul>
                            </div>
                        </div>
                    </div> 
                    </div>
                </div>
A;
            return $html.$foot;
        }//if
    }
    
    public function my_coupon_list($type,$page=null){
        if($type == "unuse"){
            $num = count($this->template['unuse']);
            $li = "unuse";
        }else if($type == "used"){
            $num = count($this->template['used']);
            $li = "used";
        }else if($type == "disabled"){
            $num = count($this->template['disabled']);
            $li = "disabled";
        }
        $html = "";
        
        for($key=0;$key<$num;$key++){
            if(isset($page)){
                if($page == "myused"){
                    $consum_code = "";
                    $share_code = "<a  href='#coupon_detail{$this->template[$li][$key]['cou_id']}'><span class='icon icon-right'></span></a>";
                }else if($page == "mydisabled"){
                    $consum_code = "";
                    $share_code = "";
                }
            }else{
                $consum_code = "<a  onclick='notice()' href='my_share_page.php?type=use&cou_id={$this->template[$li][$key]['cou_id']}' class='icon icon-code pull-right'></a>";
                $share_code = "<a  href='#coupon_detail{$this->template[$li][$key]['cou_id']}'><span class='icon icon-right'></span></a>";
            }
            $html .= <<<A
            
                <div class="card">
                    <div class="card-header">
                    {$this->template[$li][$key]['title']}
                    {$share_code}
                    </div>
                    <div class="card-content">
                    <div class="card-content-inner">{$this->template[$li][$key]['intro']}</div>
                    </div>
                    <div class="card-footer">{$this->template[$li][$key]['type']}
                    {$consum_code}
                    </div>
                  </div>
                    
A;
        }
                return $html;
    }
    
    public function show_coupon_list(){
        $html = "";
        for($i=0;$i<$this->get_num_of_template();$i++){
            $html .= "<option value='{$this->template[$i]['cou_id']}'>{$this->template[$i]['cou_title']}</option>";
        }

        return $html;
    }
    //show the share record
    public function show_share_record(){
        $html = "";
        for($i=0;$i<$this->get_num_of_template();$i++){
            $html .= <<<A
                 <li class="item-content">
                   
                    <div class="item-inner">
                      <div class="item-title">【{$this->template[$i]['title']}】</div>
                      <div class="item-after">分享给【{$this->template[$i]['user_id']}】</div>
                      <a href="" id="father_info{$this->template[$i]['share_id']}" onclick="show_record(this.id,'{$this->template[$i]['share_id']}')" class="icon icon-right pull-right"></a>
                    </div>
                  </li>
                  <li id="son_info{$this->template[$i]['share_id']}"></li>
A;
        }//for
        return $html;
    }

}
