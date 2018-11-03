#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_int(int signo,siginfo_t *info,void *tx){
	printf("SIGINT:");
	printf("si_signo:%d,sival_int:%d\n",info->si_signo,info->si_value.sival_int);
}
static void sig_usr(int signo,siginfo_t *info,void *tx){
	printf("SIGUSR1:");
	printf("si_signo:%d,sival_int:%d\n",info->si_signo,info->si_value.sival_int);
}

int main(){
	struct sigaction intact,usract,oldact;
	sigset_t sigint,sigusr;
	pid_t pid;
	union sigval val;

	intact.sa_sigaction = sig_int;
	intact.sa_flags = SA_SIGINFO;
	sigemptyset(&intact.sa_mask);

	usract.sa_sigaction = sig_usr;
	usract.sa_flags = SA_SIGINFO;
	sigemptyset(&usract.sa_mask);

	if(sigaction(SIGINT,&intact,&oldact) < 0){
		err_sys("sigaction error");
	}
	if(sigaction(SIGUSR1,&usract,NULL) < 0){
		err_sys("sigaction error");
	}
	
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		val.sival_int = 1001;
		if(sigqueue(getpid(),SIGINT,val) < 0){
			err_sys("sigqueue error");
		}
		printf("child send SIGINT\n");
		exit(0);
	}else{
		val.sival_int = 1002;
		if(sigqueue(getpid(),SIGUSR1,val) < 0){
			err_sys("sigqueue error");
		}
		printf("parent sen SIGUSR1\n");

	}

	exit(0);
}	
