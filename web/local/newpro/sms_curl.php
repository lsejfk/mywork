<?php
header("Content-Type: text/html; charset=utf-8");
function Post($curlPost,$url){
		$curl = curl_init();
		curl_setopt($curl, CURLOPT_URL, $url);
		curl_setopt($curl, CURLOPT_HEADER, false);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($curl, CURLOPT_NOBODY, true);
		curl_setopt($curl, CURLOPT_POST, true);
		curl_setopt($curl, CURLOPT_POSTFIELDS, $curlPost);
		$return_str = curl_exec($curl);
		curl_close($curl);
		return $return_str;
}

$target = "http://sms.106jiekou.com/utf8/sms.aspx";
//替换成自己的测试账号,参数顺序和wenservice对应
$post_data = "account=MichaelShen&password=2015ygrdjm.&mobile=15801891537&content=".rawurlencode("您的订单编码：4557。如需帮助请联系客服。");

echo $gets = Post($post_data, $target);

//采用UTF-8编码,要将文件另存为UTF-8格式
//请自己解析$gets字符串并实现自己的逻辑
//100 表示成功,其它的参考文档

?>