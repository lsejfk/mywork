<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
include_once '/var/www/html/weipro/module/mysql.class.php';

$mysqlObj = new Module();

while(!$mysqlObj->auto_disable_coupon()){
    ;
}
