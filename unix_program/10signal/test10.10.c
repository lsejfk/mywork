#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

int main(){
	int count = 0;
	struct timespec tsp;
	struct tm *curtm;
	char timebuf[64];
	while(1){
		sleep(60);
		count++;
		if(count == 5){
			clock_gettime(CLOCK_REALTIME,&tsp);
			strftime(timebuf,64,"%F %T %A",gmtime(&tsp.tv_sec));
			printf("%s\n",timebuf);
			count = 0;
		}
	}
	exit(0);
}
