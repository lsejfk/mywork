<?php
/*
*Created by Michael Shen
*Date:2018-09-10
*Time:21:08
*Dec:receive data from form and check input
*/
class ReceiveDate{
    private $data;
    private $data_from;
    
    public function __construct($page,$type){
        $this->data_from['page'] = $page;
        $this->data_from['type'] = $type;
    }
    
    public function get_data_from_form($type,$elem){
        if($type == "get"){
            foreach ($elem as $key=>$val){
                $this->data[$key] = $val;
            }//foreach
        }else if($type == "post"){
            foreach ($elem as $key=>$val){
                $this->data[$key] = $val;
            }
        }
    }
    
    //escape data
    public function get_data($key){
        return $this->data[$key];
    }
    
    public function get_data_page(){
        return $this->data_from['page'];
    }
 
}