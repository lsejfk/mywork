<?php
/*
*Created by Michael Shen
*Date:2018-09-10
*Time:21:31
*Dec:store the login status
*/
class LoginStatus{
    private $status;
    private $user_id;
    
    public function __construct(){
        $this->status = 0;  //no login
    }
    
    public function set_login_status($stat){
        $this->status = $stat;
    }
    
    public function get_login_status(){
        return $this->status;
    }
    
    public function set_user_id($id){
        $this->user_id = $id;
    }
    
    public function  get_user_id(){
        return $this->user_id;
    }
}

$GLO_LOGIN_STATUS = new LoginStatus();