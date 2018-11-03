

$(function(){
	$(document).on('click','.alert-text',function (event){
		if(this.id == "myregister"){
			//check the phone number
			var str = "";
			var user_id = document.getElementById("register_user_id");
			var psw = document.getElementById("register_user_psw");
			var psw1 = document.getElementById("register_user_psw1");
			if(user_id.value.length != 11){
				str = str + "电话号码不合法！";
			}
			if(str.length > 0){
				$.alert(str);
				return false;
			}
			//check the yzcode
			var user_input_code = document.getElementById("user_yzcode").value
			if(user_input_code != ser_code){
				$.alert("验证码不正确！");
				return false;
			}
			
			//check the password
			var num = psw.value;
			var num1 = psw1.value;
			if(num.length == 0){
				str = str + "密码为空！";
			}else if(num.length > 32){
				str = str + "密码长度不能超过32！";
			}else if(psw.value != psw1.value){
				str = str + "两次输入密码不一致！";
			}
			if(str.length > 0){
				$.alert(str);
				return false;
			}
		}else if(this.id == "mylogin"){
			var login_id = document.getElementById("login_user_id");
			var password = document.getElementById("login_user_psw");
			var str = "";
			if(login_id.value.length != 11){
				str = str + "电话号码不合法！";
			}
		    if(str.length > 0){
		    	$.alert(str);
		    	return false;
		    }
			//check the password
		    if(password.value.length == 0){
				str = str + "密码为空！";
			}else if(password.value.length > 32){
				str = str + "密码长度不能超过32！";
			}
		    if(str.length > 0){
				$.alert(str);
				return false;
			}
		}else if(this.id == "add_submit"){
			var add_coupon_title = document.getElementById("add_coupon_title").value;
			var add_coupon_type_select = document.getElementById("add_select_coupon_type").value;
			var add_select_time_type = document.getElementById("add_select_time_type").value;
			var textarea_detail = document.getElementById("textarea_detail").value;
			var share_reward_type = document.getElementById("share_reward_type").value;
			var add_share_times = document.getElementById("add_share_times").value;
			if(add_coupon_title.length == 0){
				$.alert("标题不能为空！");
				return false;
			}else if(add_coupon_title.length > 64){
				$.alert("标题长度不能超过64个字符！");
				return false;
			}
			
			//满减
			if(add_coupon_type_select == "1"){
				var add_input_money = document.getElementById("input_money").value;
				var add_input_coupon_money = document.getElementById("add_input_coupon_money").value;
				if(add_input_money.length == 0){
					$.alert("基础金额不能为空！");
					return false;
				}
				if(add_input_coupon_money.length == 0){
					$.alert("优惠金额不能为空！");
					return false;
				}
				if(isNaN(Number(add_input_money))){
					$.alert("基础金额不是数字！");
					return false;
				}
				if(isNaN(Number(add_input_coupon_money))){
					$.alert("优惠金额不是数字！");
					return false;
				}
			}else if(add_coupon_type_select == "2"){	//折扣
				var add_input_money = document.getElementById("input_money").value;
				if(add_input_money.length == 0){
					$.alert("折扣不能为空！");
					return false;
				}
				if(isNaN(Number(add_input_money))){
					$.alert("折扣不是数字！");
					return false;
				}
			}else if(add_coupon_type_select == "4"){	//代金券
				var add_input_money = document.getElementById("input_money").value;
				if(add_input_money.length == 0){
					$.alert("代金券不能为空！");
					return false;
				}
				if(isNaN(Number(add_input_money))){
					$.alert("代金券金额不是数字！");
					return false;
				}
			//有效期
			}
			if(add_select_time_type == "128"){
				var add_input_calender = document.getElementById("add_input_calender").value;
				var d = new Date(add_input_calender);
				var now = new Date();
				if(d.getFullYear() < now.getFullYear()){
					$.alert("非法日期！");
					return false;
				}
				if(d.getFullYear() == now.getFullYear() && d.getMonth() < now.getMonth()){
					$.alert("非法日期！");
					return false;
				}
				if(d.getFullYear() == now.getFullYear() && d.getMonth() == now.getMonth() && 
						d.getDate() < now.getDate()){
					$.alert("非法日期！");
					return false;
				}
			}else if(add_select_time_type == "64"){
				var add_input_days = document.getElementById("add_input_days").value;
				if(add_input_days.length == 0){
					$.alert("有效期不能为空！");
					return false;
				}
				if(isNaN(Number(add_input_days))){
					$.alert("有效期不是数字！");
					return false;
				}
			}
			if(add_share_times.length == 0){
				$.alert("分享次数不能为空！");
				return false;
			}
			if(isNaN(Number(add_share_times))){
				$.alert("分享次数不是数字！");
				return false;
			}
			
			if(share_reward_type == "2"){
				var textarea_other_reward = document.getElementById("textarea_other_reward").value;
				if(textarea_other_reward.length == 0){
					$.alert("奖励信息不能为空！");
					return false;
				}
				if(textarea_other_reward.length > 128){
					$.alert("奖励信息不能超过128个字符！");
					return false;
				}
			}
			
			if(textarea_detail.length == 0){
				$.alert("详细介绍不能为空！");
				return false;
			}
			if(textarea_detail.length > 256){
				$.alert("详细介绍不能超过256个字符！");
				return false;
			}
				
		}else if(this.id == "getcoupon_submit"){
			var get_user_id = document.getElementById("get_user_id").value;
			if(get_user_id.length != 11){
				$.alert("手机号不合法！");
				return false;
			}
		}else if(this.id == "add_car"){
			var car_id = document.getElementById("input_car_id").value;
			 var car_type = document.getElementById("input_car_type").value;
			 var car_color = document.getElementById("input_car_color").value;
			 if(car_id.length != 7){
				 $.alert("您输入的车牌号不合法！");
				 return false;
			 }
			 if(car_type.length == 0){
				 $.alert("车型不能为空！");
				 return false;
			 }
			 if(car_color.length == 0){
				 $.alert("车颜色不能为空！");
				 return false;
			 }
		}
     });
})


//change the html according to the type
function show_coupon_type(type){
	switch(type){
	//满减
	case "1":
		document.getElementById("input_money").name="basemoney";
		document.getElementById("input_money").placeholder="输入满多少可使用该优惠券";
		document.getElementById("div_label_money").innerHTML="基础金额";
		show_full_subtra();
		break;
	//折扣
	case "2":
		document.getElementById("full_subtra_ajax").innerHTML="";
		document.getElementById("input_money").name="discount";
		document.getElementById("input_money").placeholder="8.5";
	    document.getElementById("div_label_money").innerHTML="折扣";
		break;
	case "4":
		document.getElementById("full_subtra_ajax").innerHTML="";
		document.getElementById("input_money").name="cash";
		document.getElementById("input_money").placeholder="输入代金券面额";
		document.getElementById("div_label_money").innerHTML="代金券";
		break;
	default:
		return;
	}
}

//change the html according to the time type
function show_time_list(type){
	if(type == "128"){	//截止日期类型
		show_calender();
	}else if(type == "64"){	//有效期类型
		show_days();
	}
}

//change the html according to the reward coupon type
function show_reward_list(type){
	if(type == "1"){
		show_cou_avi_list();
	}else if(type == "2"){
		show_other_list();
	}else if(type == "3"){
		remove_reward_option();
	}
}


function router_page(pageid){
	pageid = "#" + pageid;
	$.router.load(pageid);  //加载内联页面
}

function notice(){
	$.alert("温馨提示：这是消费码，不是分享码哦！");
}




//verify code countdown
function myTimer(){
	glocount -= 1;
	document.getElementById("yzm").value=count + "s后重发";
}

