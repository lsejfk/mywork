#include<stdio.h>
#include "mysql.h"

int main(void){
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	//Initialize mysql
	mysql_init(&mysql);
	//Character Set
	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"utf8");
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"your_prog_name");
//	mysql_options(&mysql,MYSQL_OPT_PROTOCOL,"MYSQL_PROTOCOL_TCP");
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","2015ygrdjm.","test",0,NULL,0)){
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
		return 0;
	}
	//Search data
	mysql_query(&mysql,"select * from pet");
	res = mysql_store_result(&mysql);
	while(row = mysql_fetch_row(res)){
		printf("%s\t",row[0]);
		printf("%s\t",row[1]);
		printf("%s\t",row[2]);
		printf("%s\t",row[3]);
		printf("%s\t",row[4]);
		printf("%s\t",row[5]);
		printf("\n");
	}//while(row=...)
	mysql_free_result(res);
	mysql_close(&mysql);
	return 0;
}
