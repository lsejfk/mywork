#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
	sigset_t sigmask,oldmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask,SIGINT);
	/*
	if(sigprocmask(SIG_BLOCK,&sigmask,&oldmask) < 0){
		err_sys("sigprocmask error");
	}
	printf("SIGINT BLOCKED\n");
	sleep(10);
	printf("SIGINT UNBLOCKED\n");
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){
		err_sys("sigprocmask error");
	}
	sleep(10);
	*/
	if(sigsuspend(&sigmask) != -1){
		err_sys("sigsuspend error");
	}
	return 0;
}
