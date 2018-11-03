#include "apue.h"
#include "myerr.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_alrm(int signo){

}

unsigned int mysleep(unsigned int seconds){
	sigset_t newset,oldset;
	struct sigaction newact,oldact;
	unsigned int unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	if(sigaction(SIGALRM,&newact,&oldact) < 0){
		err_sys("sigaction error");
	}
	sigemptyset(&newset);
	sigaddset(&newset,SIGALRM);
	if(sigprocmask(SIG_BLOCK,&newset,&oldset) < 0){
		err_sys("sigprocmask error");
	}
	alarm(seconds);
	sigdelset(&newset,SIGALRM);
	if(sigsuspend(&newset) != -1){
		err_sys("sigsuspend error");
	}
	unslept = alarm(0);
	if(sigaction(SIGALRM,&oldact,NULL) < 0){
		err_sys("sigaction error");
	}
	if(sigprocmask(SIG_SETMASK,&oldset,NULL) < 0){
		err_sys("sigprocmask error");
	}
	return unslept;
}

int main(){
	alarm(10);
	//mysleep(2);
	exit(0);
}
