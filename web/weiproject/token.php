<?php

/**
 * wechat php test
 */


//define your token

define("TOKEN", "weipro");

$wechatObj = new wechatCallbackapiTest();
$wechatObj->responseMsg();

$wechatObj->valid();


class wechatCallbackapiTest
{
    
    public function valid()
    
    {
        
        $echoStr = $_GET["echostr"];
        
        
        //valid signature , option
        
        if($this->checkSignature()){
            
            echo $echoStr;
            
            exit;
            
        }
        
    }
    
    
    public function responseMsg()
    
    {
        
        //get post data, May be due to the different environments
        
        $postStr = $GLOBALS["HTTP_RAW_POST_DATA"];
        
        
        //extract post data
        
        if (!empty($postStr)){
            
            
            $postObj = simplexml_load_string($postStr, 'SimpleXMLElement', LIBXML_NOCDATA);
            
            $fromUsername = $postObj->FromUserName;
            
            $toUsername = $postObj->ToUserName;
            
            $keyword = trim($postObj->Content);
            
            $time = time();
            
            $textTpl = "<xml>
                
                            <ToUserName><![CDATA[%s]]></ToUserName>
                
                            <FromUserName><![CDATA[%s]]></FromUserName>
                
                            <CreateTime>%s</CreateTime>
                
                            <MsgType><![CDATA[%s]]></MsgType>
                
                            <Content><![CDATA[%s]]></Content>
                
                            <FuncFlag>0</FuncFlag>
                
                            </xml>";
            
            if(!empty( $keyword ))
            
            {
                $msgType = "text";
                
                $contentStr = "感谢您关注本公众号！本店是综合性的汽车服务门店，为了为您提供最及时精准的服务，我们团队开发了一个本店优惠信息的网站，优惠多多哦！http://119.27.190.49/weipro/index.php";
                
                $resultStr = sprintf($textTpl, $fromUsername, $toUsername, $time, $msgType, $contentStr);
                
                echo $resultStr;
                
            }else{
                
                echo "Input something...";
                
            }
            
            
        }else {
            
            echo "";
            
            exit;
            
        }
        
    }
    
    
    private function checkSignature()
    
    {
        
        $signature = $_GET["signature"];
        
        $timestamp = $_GET["timestamp"];
        
        $nonce = $_GET["nonce"];
        
        
        $token = TOKEN;
        
        $tmpArr = array($token, $timestamp, $nonce);
        
        sort($tmpArr);
        
        $tmpStr = implode( $tmpArr );
        
        $tmpStr = sha1( $tmpStr );
        
        
        if( $tmpStr == $signature ){
            
            return true;
            
        }else{
            
            return false;
            
        }
        
    }
    
}
