#include "apue.h"
#include <errno.h>
#include "myerr.h"
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

static void sig_int(int);
void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;

	if(sigprocmask(0,NULL,&sigset) < 0){
		err_ret("sigprocmask error");
	}else{
		printf("%s",str);
		if(sigismember(&sigset,SIGINT)){
			printf(" SIGINT");
		}
		if(sigismember(&sigset,SIGQUIT)){
			printf(" SIGQUIT");
		}
		if(sigismember(&sigset,SIGUSR1)){
			printf(" SIGUSR1");
		}
		if(sigismember(&sigset,SIGALRM)){
			printf(" SIGALRM");
		}
		printf("\n");
	}
	errno = errno_save;
}

int main(){
	sigset_t newset,waitset,oldset;

	if(signal(SIGINT,sig_int) == SIG_ERR){
		err_sys("signal SIGINT install failed");
	}
	sigemptyset(&newset);
	sigemptyset(&waitset);
	sigaddset(&waitset,SIGUSR1);
	sigaddset(&newset,SIGINT);

	pr_mask("main start:\n");
	if(sigprocmask(SIG_BLOCK,&newset,&oldset) < 0){
		err_sys("sigprocmask block error");
	}
	pr_mask("after block:\n");
	sigemptyset(&waitset);

	if(sigsuspend(&waitset) == -1){
		err_sys("sigsuspend error");
	}
	pr_mask("after sigsuspend finished:\n");
	if(sigprocmask(SIG_SETMASK,&oldset,NULL) < 0){
		err_sys("sigprocmask setmask error");
	}
	pr_mask("main exit:\n");
	exit(0);
}

static void sig_int(int signo){
	pr_mask("in sig_int\n");
}
