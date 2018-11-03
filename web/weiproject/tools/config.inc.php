<?php
date_default_timezone_set('Asia/Shanghai');//设置时区
session_start();
header('Content-type:text/html;charset=utf-8');
define(LOGIN_LIFETIME, 864000);     //login lifetime 10 days

define('DB_HOST','119.27.190.49');
define('DB_USER','root');
define('DB_PASSWORD','2015ygrdjm.');
define('DB_DATABASE','weipro');
define('DB_PORT',3306);

//define the type of coupon
define('FULL_SUBTRACTION', 1);  //满减
define('DISCOUNT', 2);          //折扣优惠
define('CASH', 4);              //代金券
define('DEADTIME', 128);        //指定日期
define('DAYS', 64);             //有效天数
define('COUPON_TYPE',7);        //优惠类型的掩码
define('TIME_TYPE',192);        //时间类型的掩码

?>