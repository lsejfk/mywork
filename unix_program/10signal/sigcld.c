#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static void sig_cld(int);

int main(){
	pid_t pid;

	if(signal(SIGCLD,sig_cld) == SIG_ERR){
		err_sys("signal error");
	}
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		sleep(2);
		_exit(0);
	}

	pause();
	exit(0);
}

static void sig_cld(int signo){
	pid_t pid;
	int status;

	printf("SIGCLD received\n");
	if(signal(SIGCLD,sig_cld) == SIG_ERR){
		err_sys("signal error");
	}
	if((pid = wait(&status)) < 0){
		err_sys("wait error");
	}
	printf("pid = %ld\n",pid);
}
