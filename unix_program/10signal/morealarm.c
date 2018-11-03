#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_alrm(int signo){
	printf("alrm\n");
}
unsigned int myalarm(unsigned int secodes){
	sigset_t newset,oldset,empset;
	struct sigaction alrmact,oldact;
	unsigned int unslept;

	alrmact.sa_handler = sig_alrm;
	sigemptyset(&alrmact.sa_mask);
	alrmact.sa_flags = 0;

	if(sigaction(SIGALRM,&alrmact,&oldact) < 0){
		err_sys("sigaction error");
	}

	sigemptyset(&newset);
	sigaddset(&newset,SIGALRM);
	if(sigprocmask(SIG_BLOCK,&newset,&oldset) < 0){
		err_sys("sigprocmask error");
	}

	alarm(secodes);

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
	printf("%d\n",myalarm(10));
	printf("%d\n",myalarm(5));
	return 0;
}
