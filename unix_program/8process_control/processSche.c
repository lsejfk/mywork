#include "apue.h"
#include "myerr.h"
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

unsigned long long count = 0;
struct timeval end;

void checktime(char *str){
	struct timeval cur;
	gettimeofday(&cur,NULL);

	if(cur.tv_sec >= end.tv_sec && cur.tv_usec >= end.tv_usec){
		printf("%s count = %lld\n",str,count);
		exit(0);
	}
}

int main(int argc,char *argv[]){
	int nzero,ret;
	pid_t pid;
	char *s;
	int adj = 0;

#ifdef NZERO
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	printf("NZERO = %d\n",nzero);
	if(argc != 2){
		err_quit("usage:a.out adjust");
	}

	adj = strtol(argv[1],NULL,10);

	gettimeofday(&end,NULL);
	end.tv_sec += 10;

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){		//child process
		s = "child";
		printf("current child nice number is %d,priority = %d,adjust by %d\n",nice(0)+nzero,getpriority(PRIO_PROCESS,0),adj);
		errno = 0;
		/*
		if((ret = nice(adj)) == -1 && errno != 0){
			err_sys("nice error");
		}
		*/
		if(setpriority(PRIO_PROCESS,0,adj) < 0){
			err_sys("setpriority error");
		}
		printf("now child nice number is %d\n",getpriority(PRIO_PROCESS,0));
	}else{
		s = "parent";
		printf("current parent nice number is %d\n",getpriority(PRIO_PROCESS,0));
	}

	for(;;){
		if(++count == 0){
			err_quit("%d counter wrap",s);
		}
		checktime(s);
	}
}
