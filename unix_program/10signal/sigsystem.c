#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int sigsystem(const char *cmdstr){
	int status;
	pid_t pid;
	sigset_t savesig,sigmask;
	struct sigaction ignore,saveint,savequit;

	if(cmdstr == NULL){
		return -1;
	}

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;

	if(sigaction(SIGINT,&ignore,&saveint) < 0){
		err_sys("sigaction error");
	}
	if(sigaction(SIGQUIT,&ignore,&savequit) < 0){
		err_sys("sigaction error");
	}
/*
	sigemptyset(&sigmask);
	sigaddset(&sigmask,SIGCHLD);

	if(sigprocmask(SIG_BLOCK,&sigmask,&savesig) < 0){
		err_sys("sigprocmask error");
	}
*/	
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		if(sigaction(SIGINT,&saveint,NULL) < 0){
			err_sys("sigaction error");
		}
		if(sigaction(SIGQUIT,&savequit,NULL) < 0){
			err_sys("sigaction error");
		}
		execl("/bin/sh","sh","-c",cmdstr,(char *)0);
		_exit(127);
	}else{
		sleep(30);
	/*
		while(waitpid(pid,&status,0) < 0){
			if(errno != EINTR){
				status = -1;
				break;
			}
		}
		*/
	}
	if(sigaction(SIGINT,&saveint,NULL) < 0){
		err_sys("sigaction error");
	}
	if(sigaction(SIGQUIT,&savequit,NULL) < 0){
		err_sys("sigaction error");
	}
	/*
	if(sigprocmask(SIG_SETMASK,&savesig,NULL) < 0){
		err_sys("sigprocmask error");
	}
	*/

	return status;
}

static void sig_int(int signo){
	printf("caught SIGINT\n");
}
static void sig_chld(int signo){
	printf("caught SIGCHLD\n");
}

int main(int argc,char *argv[]){
	int status;
	if(signal(SIGINT,sig_int) < 0){
		err_sys("signal(SIGINT) error");
	}
	if(signal(SIGCHLD,sig_chld) < 0){
		err_sys("signal(SIGCHLD) error");
	}
	if((status = sigsystem("/bin/ed")) < 0){
		err_sys("sigsystem error");
	}
	pr_exit(status);
	exit(0);
}
