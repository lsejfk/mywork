#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
static void pr_times(clock_t real,struct tms *starttms,struct tms *endtms);
static void do_cmd(char *cmd);

int main(int argc,char *argv[]){
	int i;
	for(i=1;i<argc;i++){
		do_cmd(argv[i]);
	}
	return 0;
}

static void do_cmd(char *cmd){
	struct tms starttms,endtms;
	clock_t start,end;
	int status;

	printf("execute command:%s\n",cmd);

	if((start = times(&starttms)) == -1){
		err_sys("times error");
	}

	if((status = system(cmd)) < 0){
		err_sys("system() error");
	}

	if((end = times(&endtms)) == -1){
		err_sys("times error");
	}

	pr_times(end-start,&starttms,&endtms);
	pr_exit(status);
}

static void pr_times(clock_t real,struct tms *starttms,struct tms *endtms){
	static long clktck = 0;
	if(clktck == 0){
		if((clktck = sysconf(_SC_CLK_TCK)) < 0){
			err_sys("sysconf error");
		}
	}

	printf("real: %7.2f\n",real / (double)clktck);
	printf("user: %7.2f\n",(endtms->tms_utime - starttms->tms_utime) / (double)clktck);
	printf("sys:  %7.2f\n",(endtms->tms_stime - starttms->tms_stime) / (double)clktck);
	printf("child user: %7.2f\n",(endtms->tms_cutime - starttms->tms_cutime) / (double)clktck);
	printf("child sys: %7.2f\n",(endtms->tms_cstime - starttms->tms_cstime) / (double)clktck);
}
