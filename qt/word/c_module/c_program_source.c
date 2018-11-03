#include "mysql.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FAIL_IN_OPEN_FILE -1
MYSQL mysql;

//Connect to the mysql server
int connectMysql(){
	//Initialize mysql
	mysql_init(&mysql);
	//Set character set
	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"utf8");
	//Build a connection
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","2015ygrdjm.","word_pro",3306,NULL,0)){
		return mysql_errno(&mysql);
	}//if(!mysql_real_connect...)
	return 0;
}

//Check if the account the user input exists in mysql 
int isAccountValid(char *account,char *passwd){
	char query_str[64];
        char query_md5[64];
	MYSQL_RES *result,*res_md5;
	MYSQL_ROW row_md5,row_column;
	strcpy(query_str,"SELECT user_id,password FROM user WHERE user_id='");
	strcat(query_str,account);
	strcat(query_str,"'");

	strcpy(query_md5,"SELECT MD5('");
	strcat(query_md5,passwd);
	strcat(query_md5,"')");

	if(mysql_query(&mysql,query_str)){
		return mysql_errno(&mysql);
	}//if(mysql_query()
	else{						//Query successed
		result = mysql_store_result(&mysql);
		if(result){				//There are rows
			row_column = mysql_fetch_row(result);
			mysql_query(&mysql,query_md5);	//Get the md5 string
			res_md5 = mysql_store_result(&mysql);
			row_md5 = mysql_fetch_row(res_md5);
			if(strcmp(account,row_column[0]) == 0 && strcmp(row_md5[0],row_column[1]) == 0){
				mysql_free_result(res_md5);
				return 1;	//Success
			}else{
				mysql_free_result(res_md5);
				return -1;	//Password error
			}
		}//if(result)
		else{				//mysql_store_result returns nothing
			mysql_free_result(result);
			return 0;		//The account is invalid
		}//else
	}//if(mysql_query) else

}


//Set login status
int setLoginStatus(const char *account,int flag){
        char query_set[64];
	if(flag == 1){
		strcpy(query_set,"UPDATE user SET login_status=1 WHERE user_id='");
	}else{
		strcpy(query_set,"UPDATE user SET login_status=0 WHERE user_id='");
	}
	strcat(query_set,account);
	strcat(query_set,"'");

	if(mysql_query(&mysql,query_set)){
		return mysql_errno(&mysql);
	}
        return 0;   //success
}


//Close the connect
void disconnectMysql(){
	mysql_close(&mysql);
}
/*
//Do the register option
int c_register(const char *account,const char *password,const char *nickname,char sex){
	char query_re[128],query_select[32];
	char query_re_escape[128];
	MYSQL_RES *res_select;
	int num;
	strcpy(query_select,"SELECT user_id FROM user WHERE user_id='");
	strcat(query_select,account);
	strcat(query_select,"'");

	if(mysql_query(&mysql,query_select)){
		return mysql_errno(&mysql);
	}

	res_select = mysql_store_result(&mysql);
	num = mysql_num_rows(res_select);
	if(num == 0){		//Haven't registered
		strcpy(query_re,"INSERT INTO user(user_id,user_name,user_sex,register_time,password,login_status) VALUES('");
		strcat(query_re,account);
		strcat(query_re,"','");
		strcat(query_re,nickname);
		if(sex == 'm'){
			strcat(query_re,"','m',CURDATE(),'");
		}else{
			strcat(query_re,"','f',CURDATE(),'");
		}
		strcat(query_re,password);
		strcat(query_re,"',1)");
		mysql_real_escape_string_quote(&mysql,query_re_escape,query_re,strlen(query_re),'\'');
		if(mysql_query(&mysql,query_re_escape)){
			return mysql_errno(&mysql);
		}
		if(mysql_affected_rows(&mysql) == 1){
			return 0;	//success
		}else{
			return 1;	//error
		}
	}else{
		return setLoginStatus(account,1);	
	}
}
*/

int c_register(const char *account,const char *password,const char *nickname,char sex){
        char query_re[248],query_select[32];
        //char query_re_escape[150];
        char str_account[20],str_password[64],str_nickname[200];
	MYSQL_RES *res_select;
	int num;
	strcpy(query_select,"SELECT user_id FROM user WHERE user_id='");
	strcat(query_select,account);
	strcat(query_select,"'");

	if(mysql_query(&mysql,query_select)){
		return mysql_errno(&mysql);
	}

	res_select = mysql_store_result(&mysql);
	num = mysql_num_rows(res_select);
        mysql_free_result(res_select);
	if(num == 0){		//Haven't registered
                strcpy(query_re,"INSERT INTO user(user_id,user_name,user_sex,register_time,password,login_status) VALUES('");
                mysql_real_escape_string_quote(&mysql,str_account,account,strlen(account),'\'');
                strcat(query_re,str_account);
		strcat(query_re,"','");
                mysql_real_escape_string_quote(&mysql,str_nickname,nickname,strlen(nickname),'\'');
                strcat(query_re,str_nickname);
		if(sex == 'm'){
                        strcat(query_re,"','m',CURDATE(),MD5('");
		}else{
                        strcat(query_re,"','f',CURDATE(),MD5('");
		}
                //printf("%s",query_re);
                mysql_real_escape_string_quote(&mysql,str_password,password,strlen(password),'\'');
                strcat(query_re,str_password);
                strcat(query_re,"'),1)");
                //mysql_real_escape_string_quote(&mysql,query_re_escape,query_re,strlen(query_re),'\'');
                printf("%s",query_re);
		if(mysql_query(&mysql,query_re)){
			return mysql_errno(&mysql);
		}
		if(mysql_affected_rows(&mysql) == 1){
			return 0;	//success
		}else{
			return 1;	//error
		}
	}else{
		return setLoginStatus(account,1);	
	}
}

//SELECT lib.word_id,lib.word,lib.phonetic,lib.definition,lib.example_en,lib.example_zh FROM word_lib lib,memorize_word mword WHERE
//mword.user_id='user_id' AND lib.word_id >= mword.start_id ORDER BY lib.word_id LIMIT 10;
//Import data in database into system file
int memorize_word_data_input(char *user_id,char *str_num,char *output_file,char *error_info){
	char query_data[258];
        char path[100] = "/home/michael/learnfile/qt/word/";
	char filename[64];
	FILE *fp;
	int num_fields,i;
	MYSQL_RES *res_data;
	MYSQL_ROW row_data;
	time_t curdate[64];
	struct tm *gmt;				//Green time
	time(curdate);				//Get current time
	gmt = gmtime(curdate);			//Transform into green time	
	strftime(filename,64,"%Y%m%d%H%M%S.txt",gmt);
	strcat(path,filename);
	strcpy(query_data,"SELECT lib.word_id,lib.word,lib.phonetic,lib.definition,lib.example_en,lib.example_zh FROM word_lib lib,memorize_word mword WHERE mword.user_id='");
	strcat(query_data,user_id);
	strcat(query_data,"' AND lib.word_id >= mword.start_id ORDER BY lib.word_id LIMIT ");
	strcat(query_data,str_num);
	if(mysql_query(&mysql,query_data)){		//There are some problem
		strcpy(error_info,mysql_error(&mysql));
		return mysql_errno(&mysql);
	}
	if((fp = fopen(path,"a+")) == NULL){		//Failed in opening file
		strcpy(error_info,"Failed in opening ");
		strcat(error_info,path);
		return FAIL_IN_OPEN_FILE;
	}
	res_data = mysql_store_result(&mysql);
	num_fields = mysql_num_fields(res_data);
	while((row_data = mysql_fetch_row(res_data))){
		for(i=0;i<num_fields;i++){
			fprintf(fp,"%s\t",row_data[i]);
		}
		putc('\n',fp);
	}
	strcpy(output_file,path);
	mysql_free_result(res_data);
	fclose(fp);
	return 0;
	

}

//Get the num_per_day from user table
int get_num_per_day(char *user_id,char *error_info){
	char query_num[64];
	MYSQL_RES *res;
	MYSQL_ROW row;
	strcpy(query_num,"SELECT num_per_day FROM user WHERE user_id='");
	strcat(query_num,user_id);
	strcat(query_num,"'");

	if(mysql_query(&mysql,query_num)){
		strcpy(error_info,mysql_error(&mysql));
		return 0;
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	error_info[0] = '\0';
	return atoi(row[0]);
}

//Record
int record_footstep(char *user_id,int num_per_day,char *error_info){
	char query_memorize[200],curdate[24];
	char query_check[200],str_start_id[10];
	int num,start_id;
	MYSQL_RES *res;
	MYSQL_ROW row;
	strcpy(query_check,"SELECT user_id,start_id,CURDATE(),m_time FROM memorize_word WHERE user_id='");
	strcat(query_check,user_id);
	strcat(query_check,"' ORDER BY m_time DESC LIMIT 1");
	
	if(mysql_query(&mysql,query_check)){
		strcpy(error_info,mysql_error(&mysql));
		return mysql_errno(&mysql);
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	num = mysql_num_rows(res);
	mysql_free_result(res);
	if(num == 1){						//There is a record
		strcpy(curdate,row[2]);
		if(strcmp(curdate,row[3]) != 0){		//Footstep hasn't been recorded
			start_id = atoi(row[1]);
			start_id += num_per_day;
			sprintf(str_start_id,"%d",start_id);
			strcpy(query_memorize,"INSERT INTO memorize_word VALUES('");
			strcat(query_memorize,user_id);
			strcat(query_memorize,"',");
			strcat(query_memorize,str_start_id);
			strcat(query_memorize,",CURDATE())");
			if(mysql_query(&mysql,query_memorize)){
				strcpy(error_info,mysql_error(&mysql));
				return mysql_errno(&mysql);
			}

			if(mysql_affected_rows(&mysql) == 1){
				return 0;
			}else{
				strcpy(error_info,"Failed in inserting record");
				return -1;
			}
		}else{//if(strcmp(curdate,row)
			strcpy(error_info,"Footstep has been recorded");
			return 1;
		}
	}else{
		strcpy(query_memorize,"INSERT INTO memorize_word(user_id,m_time) VALUES('");
		strcat(query_memorize,user_id);
		strcat(query_memorize,"',CURDATE())");
		if(mysql_query(&mysql,query_memorize)){
			strcpy(error_info,mysql_error(&mysql));
			return mysql_errno(&mysql);
		}
		if(mysql_affected_rows(&mysql) == 1){
			return 0;
		}else{
			strcpy(error_info,"Failed in inserting record");
			return -1;
		}
	}//else
}//function


//Set the plan of memorizing words
int c_set_plan(char *str_account,int num_per_day){
	char query_update[64];
	char numToStr[10];
	if(num_per_day < 0){
		return -1;
	}
	sprintf(numToStr,"%d",num_per_day);
	strcpy(query_update,"UPDATE user SET num_per_day=");
	strcat(query_update,numToStr);
	strcat(query_update," WHERE user_id='");
	strcat(query_update,str_account);
	strcat(query_update,"'");

	if(mysql_query(&mysql,query_update)){
		return mysql_errno(&mysql);
	}
	if(mysql_affected_rows(&mysql) == 1){		//Success
		return 0;
	}else{
		return 1;
	}

}


//Get the user's record
int c_get_record(char *str_user_id,int *total,int *remain){
	char query_count[100],query_all[64];
	char query_last[100];
	MYSQL_RES *res_count,*res_all,*res_last;
	MYSQL_ROW row_count,row_all,row_last;
	int num_total,num_all,num_min,num_max;
	strcpy(query_count,"SELECT start_id FROM memorize_word WHERE user_id='");
	strcat(query_count,str_user_id);
	strcat(query_count,"' ORDER BY m_time DESC LIMIT 1");

	strcpy(query_last,"SELECT start_id FROM memorize_word WHERE user_id='");
	strcat(query_last,str_user_id);
	strcat(query_last,"' ORDER BY m_time ASC LIMIT 1");

	strcpy(query_all,"SELECT COUNT(*) FROM word_lib");

	if(mysql_query(&mysql,query_count)){		//There are some problems
		return mysql_errno(&mysql);
	}
	res_count = mysql_store_result(&mysql);
	row_count = mysql_fetch_row(res_count);
	if(row_count != NULL){
		num_max = atoi(row_count[0]);
	}else{
		num_max = 0;
	}
	mysql_free_result(res_count);

	if(mysql_query(&mysql,query_last)){		//There are some problems
		return mysql_errno(&mysql);
	}
	res_last = mysql_store_result(&mysql);
	row_last = mysql_fetch_row(res_last);
	if(row_last != NULL){
		num_min = atoi(row_last[0]);
	}else{
		num_min = 0;
	}
        mysql_free_result(res_last);
	

	num_total = num_max - num_min;
	if(mysql_query(&mysql,query_all)){		//There are some problems
		return mysql_errno(&mysql);
	}
	res_all = mysql_store_result(&mysql);
	row_all = mysql_fetch_row(res_all);
	if(row_all != NULL){				//Records exist
		num_all = atoi(row_all[0]);
	}else{
		num_all = 0;
	}
	mysql_free_result(res_all);

	*total = num_total;
	*remain = num_all - num_total;
	return 0;

}


//Add my word to notebook
int c_add_my_word(char *user_id,char *word_id,char *word){
	char query_word[100];
	strcpy(query_word,"INSERT INTO word_nb(word_id,user_id,word) VALUES('");
	strcat(query_word,word_id);
	strcat(query_word,"','");
	strcat(query_word,user_id);
	strcat(query_word,"','");
	strcat(query_word,word);
	strcat(query_word,"')");

	if(mysql_query(&mysql,query_word)){
		return mysql_errno(&mysql);
	}

	if(mysql_affected_rows(&mysql) == 1){		//Success
		return 0;
	}else{
		return -1;
	}
}


//Select table word_nb and write the data into file
int c_select_word_notebook(char *user_id,int *number,char *out_file){
	char query[100];
	char path[100] = "/home/michael/learnfile/qt/word/";
	char filename[32];
	MYSQL_RES *res;
	MYSQL_ROW row;
	FILE *fp;
	int num;
	time_t curdate[64];
        struct tm *gmt;                         //Green time
        time(curdate);                          //Get current time
        gmt = gmtime(curdate);                  //Transform into green time     
        strftime(filename,64,"%Y%m%d%H%M%S.txt",gmt);
        strcat(path,filename);

	strcpy(query,"SELECT word_id,word FROM word_nb WHERE user_id='");
	strcat(query,user_id);
	strcat(query,"'");

	if(mysql_query(&mysql,query)){
		return mysql_errno(&mysql);
	}
	
	if((fp = fopen(path,"a+")) == NULL){		//Failed in opening file
		return FAIL_IN_OPEN_FILE;
	}

	res = mysql_store_result(&mysql);
	num = mysql_num_rows(res);
	while((row = mysql_fetch_row(res))){
		fprintf(fp,"%s\t",row[0]);		//word_id
		fprintf(fp,"%s\n",row[1]);		//word
	}
	strcpy(out_file,path);
	*number = num;
	mysql_free_result(res);
	fclose(fp);
	return 0;
}


//Get definition of word
int c_get_word_def(char *word_id,char *def){
	char query[100];
	MYSQL_RES *res;
	MYSQL_ROW row;
	strcpy(query,"SELECT definition FROM word_lib WHERE word_id='");
	strcat(query,word_id);
	strcat(query,"'");

	if(mysql_query(&mysql,query)){
		return mysql_errno(&mysql);
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if(row != NULL){
		strcpy(def,row[0]);
	}else{
		strcpy(def,"");
		mysql_free_result(res);
		return 1;
	}
	mysql_free_result(res);
	return 0;
}


//Delete word
int c_delete_my_word_from_note(char *word_id){
	char query[100];
	strcpy(query,"DELETE FROM word_nb WHERE word_id='");
	strcat(query,word_id);
	strcat(query,"'");

	if(mysql_query(&mysql,query)){
		return mysql_errno(&mysql);
	}
	if(mysql_affected_rows(&mysql) == 1){
		return 0;			//Success
	}else{
		return 1;
	}
}
