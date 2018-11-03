<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
//载入ucpass类
include_once '/var/www/html/weipro/lib/Ucpaas.class.php';


$appid = "bbe863b906fa46578b2da6c2e35a217d";	//应用的ID，可在开发者控制台内的短信产品下查看
$templateid = "375721";    //可在后台短信产品→选择接入的应用→短信模板-模板ID，查看该模板ID
$param = strval(rand(10000,99999)); //多个参数使用英文逗号隔开（如：param=“a,b,c”），如为参数则留空
$mobile = $_GET['user_id'];
$uid = "";
//初始化必填
//填写在开发者控制台首页上的Account Sid
$options['accountsid']='67e0428e5913e9de3cf5fd0a35f89283';
//填写在开发者控制台首页上的Auth Token
$options['token']='0ac20c3217e3f06db671dee70319f700';

//初始化 $options必填
$ucpass = new Ucpaas($options);
//70字内（含70字）计一条，超过70字，按67字/条计费，超过长度短信平台将会自动分割为多条发送。分割后的多条短信将按照具体占用条数计费。
if(!isset($_COOKIE['yzcode']['id'])){
    $ucpass->SendSms($appid,$templateid,$param,$mobile,$uid);
    
    setcookie('yzcode[id]',$mobile,time()+180);
    setcookie('yzcode[psw]',$param,time()+180);
    echo $param;
}else{
    echo "";
}

