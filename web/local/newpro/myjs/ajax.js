function send_yzcode(str)
{
	ser_code = "";
	if (str=="")
    {
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
            ser_code = xmlhttp.responseText;
        }
    }
    xmlhttp.open("POST","/weipro/smsyzm.php?user_id="+str,true);
    xmlhttp.send();
}


function show_full_subtra()
{
  var xmlhttp;
  document.getElementById("full_subtra_ajax").innerHTML="";

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
      document.getElementById("full_subtra_ajax").innerHTML=xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET","/weipro/view/ajax_handle.php?type=full_subtra&t=" + Math.random(),true);
  xmlhttp.send();
}

function show_calender()
{
  var xmlhttp;
  document.getElementById("li_time_type").innerHTML = "";
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
      document.getElementById("li_time_type").innerHTML=xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET","/weipro/view/ajax_handle.php?type=time_calender&t=" + Math.random(),true);
  xmlhttp.send();
}


function show_days()
{
  var xmlhttp;
  document.getElementById("li_time_type").innerHTML = "";
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
      document.getElementById("li_time_type").innerHTML=xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET","/weipro/view/ajax_handle.php?type=time_days&t=" + Math.random(),true);
  xmlhttp.send();
}

function show_cou_avi_list()
{
  var xmlhttp;
  document.getElementById("other_reward_list").innerHTML = "";
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
      document.getElementById("reward_cou_list").innerHTML=xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET","/weipro/view/ajax_handle.php?type=reward_cou&t=" + Math.random(),true);
  xmlhttp.send();
}

function show_other_list()
{
  var xmlhttp;
  document.getElementById("reward_cou_list").innerHTML = "";
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
      document.getElementById("other_reward_list").innerHTML=xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET","/weipro/view/ajax_handle.php?type=other_list&t=" + Math.random(),true);
  xmlhttp.send();
}

function show_record(thisid,share_id){
	var xmlhttp;
	var sonid = thisid.replace("father","son");
	var val = document.getElementById(thisid).getAttribute("class");
	if(val == "icon icon-down"){
		val = "icon icon-right";
		document.getElementById(sonid).innerHTML = "";
		document.getElementById(thisid).setAttribute("class",val);
		return;
	}else{
		val = "icon icon-down";
	}
	  
	  document.getElementById(thisid).setAttribute("class",val);
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
	      document.getElementById(sonid).innerHTML=xmlhttp.responseText;
	    }
	  }
	  var url = "/weipro/view/ajax_handle.php?type=share_record&share_id=" + share_id;
	  xmlhttp.open("GET",url,true);
	  xmlhttp.send();
}



function remove_reward_option(){
	document.getElementById("reward_cou_list").innerHTML = "";
	document.getElementById("other_reward_list").innerHTML = "";
}


//verify the yzcode
function yzm_action(){
	var uid = document.getElementById("register_user_id").value;
	var thebtn = document.getElementById("yzm");
	if(uid.length != 11){
		$.alert("电话号码不合法！");
	}else{
		
		send_yzcode(uid);
		if(ser_code.length > 0){
        	$.alert("发送成功！");
        	thebtn.setAttribute("class", "button pull-right disabled");
    		glocount = 60;
    		
    		timer = setInterval(function(){
    			if(glocount > 0){
    				glocount = glocount - 1;
    				thebtn.setAttribute("class", "button pull-right disabled");
    				thebtn.setAttribute("disabled", "disabled");
    				thebtn.innerHTML = glocount + "s后重发";
    			}else{
    				thebtn.setAttribute("class", "button pull-right");
    				thebtn.setAttribute("disabled", "");
    				thebtn.innerHTML = "获取验证码";
    				clearInterval(timer);
    			}
    		},1000);
        }else{
        	$.alert("验证码已发送！");
        }
		
	}
}




function remove_badge(){
	var xmlhttp;
	
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
	      document.getElementById("thebadge3").innerHTML=xmlhttp.responseText;
	      document.getElementById("thebadge2").innerHTML=xmlhttp.responseText;
	      document.getElementById("thebadge1").innerHTML=xmlhttp.responseText;
	    }
	  }
	  var url = "/weipro/view/ajax_handle.php?type=remove_badg";
	  xmlhttp.open("GET",url,true);
	  xmlhttp.send();
}
