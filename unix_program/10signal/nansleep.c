#include "apue.h"
#include "myerr.h"
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(){
	struct timespec tsp;
	if(clock_gettime(CLOCK_REALTIME,&tsp) < 0){
		err_sys("clock_gettime error");
	}
	printf("call clock_nanosleep()\n");
	tsp.tv_sec += 60;
	clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME,&tsp,NULL);
	return 0;
}
