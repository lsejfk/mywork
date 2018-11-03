<?php
include_once '/var/www/html/weipro/tools/tools.inc.php';
include_once '/var/www/html/weipro/controler/control.class.php';
/*
 * Created by Michael Shen
 * Date:2018-09-09
 * Time:10:18
 * Dec:Check the data received from html and show information to the html
*/
class Login{
    private $user_id;   //the phone number of user
    private $user_psw;  //the password of user
    private $controler;
    public function __construct($back=null){
        $form_data = $this->get_form_data();
        if(is_array($form_data) && !empty($form_data)){
            $this->user_id = $form_data['id'];
            $this->user_psw = $form_data['psw'];
            $this->controler = new Control();
            if($form_data['type'] == "login"){
                $this->controler->login_into($this->user_id,$this->user_psw);
            }else if($form_data['type'] == "register"){
                $this->controler->register_into($form_data,$back);
            }
        }else{
            info_to_user("没有数据！");
        }
    }
    
    //get data from form and check the input
    public function get_form_data(){
        if(isset($_POST['login'])){
            $user['type'] = "login";  //login
            $user['id'] = $_POST['user_id'];
            $user['psw'] = $_POST['user_psw'];
        }else if(isset($_POST['register'])){
            $user['type'] = "register";  //register
            $user['id'] = $_POST['user_id'];
            $user['yzm'] = $_POST['yzcode'];
            $user['psw'] = $_POST['user_psw'];
            $user['psw1'] = $_POST['user_psw1'];
            $user['gender'] = $_POST['gender'];
        }
        //check the input data
        $this->check_input($user);
        return $user;
    }
    
    //check data input
    public function check_input($data){
        if(is_array($data) && !empty($data)){
            if($data['type'] == "login"){
                if(empty($data['id'])){
                    info_to_user("手机号不得为空！");
                }
                if(mb_strlen($data['id']) != 11){
                    info_to_user("不合法手机号");
                }
                if(empty($data['psw'])){
                    info_to_user("密码不得为空！");
                }
                
            }else if($data['type'] == "register"){
                if(empty($data['id'])){
                    info_to_user("手机号不得为空！");
                }
                if(mb_strlen($data['id'])!=11){
                    info_to_user("不合法手机号");
                }
                if($data['id'] != $_COOKIE['yzcode']['id'] || $data['yzm'] != $_COOKIE['yzcode']['psw']){
                    info_to_user("验证码错误！");
                }
                if(empty($data['psw'])){
                    info_to_user("密码不得为空！");
                }
                if(empty($data['psw1'])){
                    info_to_user("确认密码不得为空！");
                }
                if(empty($data['gender'])){
                    info_to_user("性别未选！");
                }
            }//if data
        }//if is_array
    }//public function
    
}