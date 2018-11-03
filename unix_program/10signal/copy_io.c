#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>

#define BUFSIZE 100 
static void sig_intr(int signo){
	printf("caught SIGXFSZ\n");
}

int main(){
	struct sigaction xfszact,oldact;
	struct rlimit softlimit;
	char buf[BUFSIZE];
	int n,writen;

	xfszact.sa_handler = sig_intr;
	xfszact.sa_flags = 0;
	sigemptyset(&xfszact.sa_mask);
	if(sigaction(SIGXFSZ,&xfszact,&oldact) < 0){
		err_sys("sigaction error");
	}
	if(getrlimit(RLIMIT_FSIZE,&softlimit) < 0){
		err_sys("getrlimit error");
	}
	printf("the old size:%d\n",softlimit.rlim_cur);
	softlimit.rlim_cur = 1024;

	if(setrlimit(RLIMIT_FSIZE,&softlimit) < 0){
		err_sys("setrlimit error");
	}
	/*
	while((n = read(STDIN_FILENO,buf,BUFSIZE)) > 0){
		if((writen = write(STDOUT_FILENO,buf,n)) != n){
			err_sys("write error");
		}
		printf("%d writen\n",writen);
	}

	if(n < 0){
		err_sys("read error");
	}	
	*/
	exit(0);
}
