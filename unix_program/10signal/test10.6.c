#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;

static void sig_usr(int signo){
	sigflag = 1;
}

void TELL_WAIT(void){
	struct sigaction newact,oldact;

	newact.sa_handler = sig_usr;
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);

	if(sigaction(SIGUSR1,&newact,&oldact) < 0){
		err_sys("sigaction error");
	}
	if(sigaction(SIGUSR2,&newact,&oldact) < 0){
		err_sys("sigaction error");
	}

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&newmask,SIGUSR2);
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0){
		err_sys("sigprocmask error");
	}
}

void TELL_PARENT(pid_t pid){
	kill(pid,SIGUSR2);	
}

void WAIT_PARENT(){
	while(sigflag == 0){
		if(sigsuspend(&zeromask) != -1){
			err_sys("sigsupend error");
		}
	}
	sigflag = 0;
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){
		err_sys("sigprocmask error");
	}
}

void TELL_CHILD(pid_t pid){
	kill(pid,SIGUSR1);
}

void WAIT_CHILD(){
	while(sigflag == 0){
		if(sigsuspend(&zeromask) != -1){
			err_sys("sigsuspend error");
		}
	}
	sigflag = 0;
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){
		err_sys("sigprocmask error");
	}
}

int main(){
	int fd;
	pid_t pid;
	if((fd = open("test6",O_RDWR|O_CREAT|O_TRUNC),S_IRWXU) < 0){
		err_sys("open error");
	}
	if(write(fd,"0",1) != 1){
		err_sys("write error");
	}
	TELL_WAIT();
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		printf("child\n");
		if(write(fd,"1",1) != 1){
			err_sys("write error");
		}
		TELL_PARENT(getppid());
		WAIT_PARENT();
		printf("child\n");
		if(write(fd,"3",1) != 1){
			err_sys("write error");
		}
		TELL_PARENT(getppid());
		exit(0);
	}
	WAIT_CHILD();
	printf("parent\n");
	if(write(fd,"2",1) != 1){
		err_sys("write error");
	}
	TELL_CHILD(pid);
	WAIT_CHILD();
	printf("parent\n");
	if(write(fd,"4",1) != 1){
		err_sys("write error");
	}
	exit(0);
}
