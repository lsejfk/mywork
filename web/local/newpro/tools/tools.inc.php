<?php
/*
 * Created by Michael Shen 
 * Date:2018-09-09
 * Time:11:08
 * Dec:provide the tool function for using
*/
function skip($url){
    $html=<<<A
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<meta http-equiv="refresh" content="0;URL={$url}" />
<title>正在跳转中</title>
</head>
<body>
</body>
</html>
A;
    echo $html;
    exit();
}


//note
function info_to_user($mes,$pic="info",$btn="确定",$url=null,$router=false){
    if($url == null){
        $back = "back";
    }else{
        $back = "";
    }
    $html=<<<A
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>提示</title>
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
            <div class="content">
                <div class="content-block">
                   <div style="text-align:center;padding:20px 0px 0px 0px"><img style="height:100px;width:100px" src="/weipro/style/{$pic}.png" alt=""></div>
                   <p style="text-align:center;padding:0px 0px 20px 0px">{$mes}</p>
                   <p><a href="{$url}" class="button button-dark button-big {$back}" data-no-cache="{$router}">{$btn}</a></p>
                </div>
            </div>
        </div>
    </div>
    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>

  </body>
</html>
A;
echo $html;
    exit();
}

function confirm($mes,$url,$pic="info"){
    $html=<<<A
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>提示</title>
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
            <div class="content">
                <div class="content-block">
                   <div style="text-align:center;padding:20px 0px 0px 0px"><img style="height:100px;width:100px" src="/weipro/style/{$pic}.png" alt=""></div>
                   <p style="text-align:center;padding:0px 0px 20px 0px">{$mes}</p>
                   <p><a href="{$url}" class="button button-big ">确定</a></p>
                   <p><a href="" class="button button-dark button-big back">取消</a></p>
                </div>
            </div>
        </div>
    </div>
    <script type='text/javascript' src='//g.alicdn.com/sj/lib/zepto/zepto.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm.min.js' charset='utf-8'></script>
    <script type='text/javascript' src='//g.alicdn.com/msui/sm/0.6.2/js/sm-extend.min.js' charset='utf-8'></script>
                       
  </body>
</html>
A;
    echo $html;
    exit();
}
