#include<time.h>
#include<stdio.h>
#include "test.h"
#include<stdio.h>

int main(){
	char out[64],err[64];
	time_t t[64];
	struct tm *gmt;
	int errno;
	int total,remain;
	connectMysql();
//	isAccountValid("15801891537","2015ygrdjm.");
//	errno = record_footstep("15801891537",32,err);
//	printf("errno=%d,err:%s\n",errno,err);
//	errno = memorize_word_data_input("15801891537","10",out,err);

//	printf("%d,err:%s,path:%s",errno,err,out);
//	printf("%d,%s",get_num_per_day("15801891537",err),err);
//	time(t);
//	gmt = gmtime(t);
//	strftime(out,64,"%Y%m%d%H%M%S.txt",gmt);
//	printf("%s",out);
//	errno = c_get_record("15801891537",&total,&remain);
//	printf("Errno:%d,total%d,remain%d",errno,total,remain);
	errno = c_select_word_notebook("15801891537",out);
	printf("errno%d\toutfile%s\n",errno,out);
	return 0;
}
