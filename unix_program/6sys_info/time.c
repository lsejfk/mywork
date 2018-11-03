#include "apue.h"
#include "myerr.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int main(){
	time_t tt;
	struct tm *bt,*bd;
	struct timespec ts;
	struct timeval tv;
	char buf1[64];
	char buf2[64];
	time(&tt);	//get UTC
	if(clock_getres(CLOCK_REALTIME,&ts) < 0){
		err_sys("clock_getres error");
	}
	if(clock_gettime(CLOCK_REALTIME,&ts) < 0){
		err_sys("clock_gettime error");
	}
	if((bt = gmtime(&tt)) == NULL){
		err_sys("gmtime error");
	}
	if((bd = localtime(&ts.tv_sec)) == NULL){
		err_sys("localtime error");
	}
	if(strftime(buf1,64,"%c",bt) == 0){
		err_ret("the buf is too small");
	}else{
		printf("time():%s\n",buf1);
	}
	if(strftime_l(buf2,64,"%F %T",bd,"Hong_Kong") == 0){
		err_ret("the buf is too small");
	}else{
		printf("clock_gettime:%s",buf2);
	}
	return 0;
}
