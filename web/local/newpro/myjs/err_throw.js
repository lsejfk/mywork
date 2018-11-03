function myFunction() {
    var message, x;
    message = document.getElementById("message");
    message.innerHTML = "";
    x = document.getElementById("demo").value;
    try { 
        if(x == "")  throw "值为空";
        if(isNaN(x)) throw "不是数字";
        x = Number(x);
        if(x < 5)    throw "太小";
        if(x > 10)   throw "太大";
    }
    catch(err) {
        message.innerHTML = "错误: " + err;
    }
}

function check_user_id(type){
	var user_id;
	var str = "";
	user_id = document.getElementById(type);
	
	if(user_id.value.length != 11){
		str = str + "电话号码不合法！";
	}
	return str;
}

function check_user_psw(type1,type2){
	var user_psw,user_psw1,num,num1;
	var str = "";
	user_psw = document.getElementById(type1);
	user_psw1 = document.getElementById(type2);
	num = user_psw.value.length;
	num1 = ser_psw1.value.length;
	if(num == 0){
		str = str + "密码为空！";
	}else if(num > 32){
		str = str + "密码长度不能超过32！";
	}else if(user_psw.value != user_psw1.value){
		str = str + "两次输入密码不一致！";
	}
	return str;
}

function check_user_yzm(code){
	var input_code;
	input_code = document.getElementById("user_yzcode");
	var value;
	var str = "";
	value = input_code.value;
	if(value != code){
		str = str + "验证码不正确！";
	}
	return str;
}


//check the information the user input when logining
function check_user_login(){
	var str = "";
	str = check_user_id("login_user_id");
	if(str.length > 0){		//error
		return str;
	}
	str = check_user_psw("login_user_psw");
	if(str.length > 0){
		return str;
	}
	return str;
}


    


//check the information the user input when logining
function check_user_register(){
	var str = "";
	str = check_user_id("register_user_id");
	//check user id
	if(str.length > 0){
		return str;
	}
	str = check_user_yzm("user_yzcode");
	if(str.length > 0){
		return str;
	}
	str = check_user_psw("register_user_psw","register_user_psw1");
	if(str.length > 0){
		return str;
	}
	return str;
}


function showSite(str)
{
    if (str=="")
    {
        document.getElementById("txtHint").innerHTML="";
        return;
    } 
    if (window.XMLHttpRequest)
    {
        // IE7+, Firefox, Chrome, Opera, Safari 浏览器执行代码
        xmlhttp=new XMLHttpRequest();
    }
    else
    {
        // IE6, IE5 浏览器执行代码
        xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
    xmlhttp.onreadystatechange=function()
    {
        if (xmlhttp.readyState==4 && xmlhttp.status==200)
        {
            document.getElementById("txtHint").innerHTML=xmlhttp.responseText;
        }
    }
    xmlhttp.open("GET","getsite_mysql.php?q="+str,true);
    xmlhttp.send();
}

// go back
function go_back(mes){
	alert(mes);
	window.history.back(-1);
}

//go to the specified page
function go_to_page(var url){
	window.location.href = url;
}