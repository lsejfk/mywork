<?php
include_once '/var/www/html/weipro/tools/config.inc.php';
/*
*Created by Michael Shen
*Date:2018-09-09
*Time:13:45
*
*Dec:database interface
 */


class Module{
    private $link;  //the link of database
    

    
    //数据库连接
    public function __construct($host=DB_HOST,$user=DB_USER,$password=DB_PASSWORD,$database=DB_DATABASE,$port=DB_PORT){
        $mylink=@mysqli_connect($host, $user, $password, $database, $port);
        if(mysqli_connect_errno()){
            exit(mysqli_connect_error());
        }
        mysqli_set_charset($mylink,'utf8');
        mysqli_query($mylink, "set names 'utf8'");
        $this->link = $mylink;
    }

    
    
    //执行一条SQL语句,返回结果集对象或者返回布尔值
    public function execute($query){
        $result=mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            exit(mysqli_error($this->link));
        }
        return $result;
    }
    //执行一条SQL语句，只会返回布尔值
    public function execute_bool($query){
        $bool=mysqli_real_query($this->link,$query);
        if(mysqli_errno($this->link)){
            exit(mysqli_error($this->link));
        }
        return $bool;
    }
    
    //获取记录数
    public function num($sql_count){
        $result=$this->execute($sql_count);
        $count=mysqli_fetch_row($result);
        return $count[0];
    }
    //数据入库之前进行转义，确保，数据能够顺利的入库
    public function escape($data){
        if(is_string($data)){
            return mysqli_real_escape_string($this->link,$data);
        }
        if(is_array($data)){
            foreach ($data as $key=>$val){
                $data[$key]=$this->escape($val);
            }
        }
        return $data;
        //mysqli_real_escape_string($link,$data);
    }
    
    
    //关闭与数据库的连接
    public function close(){
        mysqli_close($this->link);
    }
    
    //check if the user exists
    public function is_user_exist($user_id){
        $query = "SELECT user_id FROM user WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        if(mysqli_num_rows($result) == 0){
            return false;
        }else{
            return true;
        }
    }
    
    //login
    public function login($user_id,$user_psw){
        $query = "SELECT user_id,user_psw FROM user WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        $data_result = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        //confirm the password
        if($data_result['user_id'] == $user_id && $data_result['user_psw'] == md5($user_psw)){
            $query_login = "UPDATE user SET user_status=1,user_lgtime=NOW() WHERE user_id='{$user_id}'";
            if($this->execute_bool($query_login)){
                return true;
            }       
        }
        return false;
    }
    
    public function logout($user_id){
        $query = "UPDATE user SET user_status=0 WHERE user_id='{$user_id}'";
        $this->execute($query);
        return true;
    }
    
    //register
    public function register($user_id,$user_psw,$user_gender){
        //handle the input data
        $user_psw = $this->escape($user_psw);
        $query = "INSERT INTO user(user_id,user_level,user_rgtime,user_sex,user_status,user_lgtime,user_psw)
        VALUES('{$user_id}',1,NOW(),'{$user_gender}',1,NOW(),MD5('{$user_psw}'))";
        $this->execute($query);
        if(mysqli_affected_rows($this->link) == 1){
            return true;
        }
        return false;
    }
    
    //select the database check if exist the user with the password
    public function confirm_id_with_psw($user_id){
        $query = "SELECT user_status FROM user WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        if($data['user_status'] == 1){   //login
            return true;
        }
        return false;
    }
    //check if the user is menager
    public function isMenager($user_id){
        $query = "SELECT user_level FROM user WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        if($data['user_level'] == 0){
            return true;
        }
        return false;
    }
    
    
    //submit data
    public function submit_data($data,$table){
        if($table == "coupon"){
            //escape special character
            $data = $this->escape($data);
            if($data['type'] & DEADTIME){
                if($data['reward_type'] == 1){  //优惠券
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,reward_id,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),DATEDIFF(DATE('{$data['end']}'),NOW()),DATE('{$data['end']}'),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},{$data['reward_id']},{$data['cou_times']})";
                }else if($data['reward_type'] == 2){
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,reward_info,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),DATEDIFF(DATE('{$data['end']}'),NOW()),DATE('{$data['end']}'),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},'{$data['reward_info']}',{$data['cou_times']})";
                }else if($data['reward_type'] == 3){
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),DATEDIFF(DATE('{$data['end']}'),NOW()),DATE('{$data['end']}'),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},{$data['cou_times']})";
                }else{
                    return false;
                }
            }else if($data['type'] & DAYS){
                if($data['reward_type'] == 1){  //优惠券
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,reward_id,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),{$data['days']},ADDDATE(DATE(NOW()),{$data['days']}),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},{$data['reward_id']},{$data['cou_times']})";
                }else if($data['reward_type'] == 2){
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,reward_info,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),{$data['days']},ADDDATE(DATE(NOW()),{$data['days']}),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},'{$data['reward_info']}',{$data['cou_times']})";
                }else if($data['reward_type'] == 3){
                    $query = "INSERT INTO coupon(cou_title,cou_type,cou_start,cou_days,cou_end,cou_base,cou_discount,cou_info,cou_level,reward_type,cou_times) VALUES('{$data['title']}',{$data['type']},NOW(),{$data['days']},ADDDATE(DATE(NOW()),{$data['days']}),{$data['base']},{$data['discount']},'{$data['info']}',{$data['level']},{$data['reward_type']},{$data['cou_times']})";
                }else{
                    return false;
                }
            }else{
                return false;
            }
            $this->execute($query);
            if(mysqli_affected_rows($this->link) == 1){
                return true;
            }else{
                return false;
            }
        }else if($table == "car"){

            $data = $this->escape($data);
            $query = "INSERT INTO car(car_id,user_id,car_type,car_color) VALUES('{$data['car_id']}','{$data['user_id']}','{$data['car_type']}','{$data['car_color']}')";
            $this->execute($query);
            if(mysqli_affected_rows($this->link) == 1){
                return true;
            }else{
                return false;
            }
            
        }
        
    }
    
    //select the hole coupon table,return the data
    public function get_cou_data($indentify="cou",$cou_id=null,$user_id=null){
        if($indentify == "cou"){
            $query = "SELECT * FROM coupon ORDER BY cou_start DESC";
        }else if($indentify == "cou_title"){
            $query = "SELECT cou_id,cou_title FROM coupon";
        }else if($indentify == "specify"){
            $query = "SELECT * FROM coupon WHERE cou_id=$cou_id";
        }else if($indentify == "myunuse"){  //unused coupon
            $query = "SELECT * FROM coupon WHERE cou_id IN (SELECT cou_id FROM get WHERE user_id='{$user_id}' AND cou_status=0)";
        }else if($indentify == "myused"){   //used coupon
            $query = "SELECT * FROM coupon WHERE cou_id IN (SELECT cou_id FROM get WHERE user_id='{$user_id}' AND cou_status=1)";
        }else if($indentify == "mydisabled"){   //disabled coupon
            $query = "SELECT * FROM coupon WHERE cou_id IN (SELECT cou_id FROM get WHERE user_id='{$user_id}' AND cou_status=2)";
        }
        $result = $this->execute($query);
        $dataArr = array();
        $i = 0;
        while(($data = mysqli_fetch_assoc($result))){
            $dataArr[$i++] = $data;
        }
        mysqli_free_result($result);
        return $dataArr;
    }
    
    //select the coupon of the user
    
    
    public function coupon_title($cou_id){
        $query = "SELECT cou_title FROM coupon WHERE cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        return $data['cou_title'];
    }
    
    public function delete_cou_by_id($cou_id){
        mysqli_autocommit($this->link, false);
        $query = "DELETE FROM coupon WHERE cou_id=$cou_id";
        $this->execute($query);
        if(mysqli_affected_rows($this->link) != 1){
            mysqli_rollback($this->link);
            mysqli_autocommit($this->link, true);
            return false;
        }
        $query = "DELETE FROM share WHERE cou_id=$cou_id";
        if(!$this->execute_bool($query)){
            mysqli_rollback($this->link);
            mysqli_autocommit($this->link, true);
            return false;
        }
        
        $query = "DELETE FROM get WHERE cou_id=$cou_id";
        if(!$this->execute_bool($query)){
            mysqli_rollback($this->link);
            mysqli_autocommit($this->link, true);
            return false;
        }
        if(!mysqli_commit($this->link)){
            mysqli_rollback($this->link);
            mysqli_autocommit($this->link, true);
            return false;
        }
        mysqli_autocommit($this->link, true);
        return true;
    }
    
    
    //get the reward information
    public function get_reward_coupon_info($cou_id){
        $query = "SELECT cou_title,cou_type,cou_base,cou_discount FROM coupon WHERE cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        return $data;
    }
    
    public function insert_share_record($share_user,$cou_id,$to_user,$share_times){
        //由于在事务提交中系统默认提交，故这里设置为FALSE先不提交
        mysqli_autocommit($this->link,false);
        
        //其实这里系统已经相当在这里做个保存点，记录此时所有状态，回滚是回滚到这里
        //$mysqli->savepoint a;
        $query = "SELECT user_id FROM share WHERE to_user_id='{$to_user}' AND cou_id=$cou_id AND user_id='{$to_user}'";

        $result = mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_num_rows($result) > 0){
            $res1 = false;
        }else{
            $res1 = true;
        }

        $query = "SELECT user_id FROM get WHERE user_id='{$to_user}' AND cou_id=$cou_id";

        $result = mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_num_rows($result) > 0){
            $res2 = false;
        }else{
            $res2 = true;
        }
        
        if($res2 == false || $res1 == false){
            mysqli_autocommit($this->link,true);
            return "exist";
        }

        $share_id = time()."-".rand(10000,99999);
        $query = "INSERT INTO share(share_id,user_id,cou_id,to_user_id,share_time) VALUES('{$share_id}','{$share_user}',$cou_id,'{$to_user}',NOW())";

        $result = mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_affected_rows($this->link) != 1){
            $res3 = false;
        }else{
            $res3 = true;
        }


        $query = "SELECT share_id FROM share WHERE to_user_id='{$to_user}' AND user_id='{$share_user}' AND cou_id=$cou_id";

        $result = mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_num_rows($result) == 0){
            $res4 = false;
        }else{
            $res4 = true;
        }
        $data = mysqli_fetch_assoc($result);
        $query = "INSERT INTO get(user_id,cou_id,get_time,share_times,getid) VALUES('{$to_user}',{$cou_id},NOW(),{$share_times},'{$share_id}')";

        $result = mysqli_query($this->link,$query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_affected_rows($this->link) != 1){
            $res5 = false;
        }else{
            $res5 = true;
        }
        $err = "";
        if(!$res1 || !$res2 || !$res3 || !$res4 || !$res5){
            //只要有一条失败便回滚，都不执行,若设置滚回点，如a,加个参数a变滚回到a处
            mysqli_rollback($this->link);
            mysqli_autocommit($this->link,true);
            return "error";
        }else{
            //一旦提交无法回滚，成功则提交
            if(!mysqli_commit($this->link)){
                mysqli_autocommit($this->link,true);
                return "error";
            }
        }
        
        mysqli_autocommit($this->link,true);
        return "success";
    }
    
    //return the coupon share times 
    public function get_stimes_of_coupon($cou_id){
        $query = "SELECT cou_times FROM coupon WHERE cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        return $data['cou_times'];
    }
    
    public function get_stimes_of_user($user_id,$cou_id){
        $query = "SELECT share_times FROM get WHERE user_id='{$user_id}' AND cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        return $data['share_times'];
    }
    
    public function set_times($user_id,$cou_id){
        $query = "UPDATE get SET share_times=share_times-1 WHERE user_id='{$user_id}' AND cou_id=$cou_id";
        $this->execute($query);
        if(mysqli_errno($this->link)){
            echo mysqli_error($this->link);
            exit();
        }
        if(mysqli_affected_rows($this->link) == 1){
            return true;
        }else{
            return false;
        }
    }
    
    public function get_share_record_by_id($share_id){
        $query = "SELECT * FROM share WHERE share_id='{$share_id}'";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        return $data;
    }
    
    public function get_share_records($user_id){
        $query = "SELECT * FROM share WHERE user_id=$user_id order by share_time desc";
        $result = $this->execute($query);
        $dataArr = array();
        $i = 0;
        while($data = mysqli_fetch_assoc($result)){
            $dataArr[$i++] = $data;
        }
        return $dataArr;
    }
    
    public function is_used($user_id,$cou_id){
        $query = "SELECT cou_status FROM get WHERE user_id=$user_id AND cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        if($data['cou_status'] == 1){
            return true;
        }
        return false;
    }
    
    public function is_disabled($user_id,$cou_id){
        $query = "SELECT cou_status FROM get WHERE user_id=$user_id AND cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        if($data['cou_status'] == 2){
            return true;
        }
        return false;
    }
    
    public function module_use_coupon($user_id,$cou_id){
        
        $query = "SELECT cou_status FROM get WHERE user_id=$user_id AND cou_id=$cou_id";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        if($data['cou_status'] == 1){
            return "used";
        }else if($data['cou_status'] == 2){
            return "disabled";
        }
        mysqli_free_result($result);
        mysqli_autocommit($this->link,false);
        //update the get table
        $query = "UPDATE get SET cou_status=1 WHERE user_id=$user_id AND cou_id=$cou_id";
        $this->execute($query);
        if(mysqli_affected_rows($this->link) == 1){
            $res1 = true;
        }else{
            $res1 = false;
        }
        //update the share table
        $query = "UPDATE share SET status=1 WHERE to_user_id=$user_id AND cou_id=$cou_id";
        $this->execute($query);
        if(mysqli_affected_rows($this->link) == 1){
            $res2 = true;
        }else{
            $res2 = false;
        }
        
        if($res1 && $res2){ //commit only when the two actions all success
            if(!mysqli_commit($this->link)){
                mysqli_autocommit($this->link,true);
                return "error";
            }
            mysqli_autocommit($this->link,true);
            return "success";
        }
        mysqli_autocommit($this->link,true);
        return false;
        
    }
    
    public function module_get_new_share_record($user_id){
        $query = "SELECT COUNT(*) num FROM share WHERE user_id=$user_id AND share_time>CURDATE()";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        if(empty($data)){
            return 0;
        }
        return $data['num'];
    }
    
    public function set_autocommit($mode){
        mysqli_autocommit($this->link, $mode);
    }
    
    public function rollback(){
        return mysqli_rollback($this->link);
    }
    
    public function commit(){
        return mysqli_commit($this->link);
    }
    
    
    public function auto_disable_coupon(){
        $query = "SELECT * FROM coupon";
        $result = $this->execute($query);
        mysqli_autocommit($this->link, false);      //set do not autocommit
        $flag = true;
        $data = mysqli_fetch_assoc($result);
        
        while($flag && !empty($data)){
            $query = "select user_id,cou_id,cou_status,get_time FROM get WHERE cou_id={$data['cou_id']}";
            $theResult = $this->execute($query);
           
            while($theData = mysqli_fetch_assoc($theResult)){
                if($theData['cou_status'] == 1 || $theData['cou_status'] == 2){    //used or disabled
                    continue;
                }
                if($data['cou_type'] & 192 == 128){ //deadline type
                    if(time() > strtotime($data['cou_end'])){
                        $query = "UPDATE get SET cou_status=2 WHERE user_id='{$theData['user_id']} AND cou_id={$theData['cou_id']}";
                        $this->execute($query);
                        if(mysqli_affected_rows($this->link) != 1){
                            $flag = false;  //failed ,skip out the loop
                            mysqli_rollback($this->link);
                            break;
                        }
                    }//if
                }else if($data['cou_type'] & 192 == 64){
                    if(time() > (strtotime($theData['get_time']) + $data['cou_days'] * 24 * 3600)){
                        $query = "UPDATE get SET cou_status=2 WHERE user_id='{$theData['user_id']} AND cou_id={$theData['cou_id']}";
                        $this->execute($query);
                        if(mysqli_affected_rows($this->link) != 1){
                            $flag = false;  //failed ,skip out the loop
                            mysqli_rollback($this->link);
                            break;
                        }
                    }//if
                }//if data
            }//while $theData
            
            $data = mysqli_fetch_assoc($result);
        }//while flag
        
        if($flag){  //all the queries have execute correctly
            mysqli_commit($this->link);
            return true;
        }else{
            return false;
        }
        
    }
    
    //check if the user have band the car id
    public function modbandcar($user_id){
        $query = "SELECT car_id FROM car WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        if(mysqli_num_rows($result) == 1){
            return true;
        }else{
            return false;
        }
    }
    
    //get the user's car information
    public function modget_car_info($user_id){
        $query = "SELECT * FROM car WHERE user_id='{$user_id}'";
        $result = $this->execute($query);
        $data = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
        return $data;
    }
    
    
}
