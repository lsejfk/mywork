#include "apue.h"
#include "myerr.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int my_system(const char *cmdstring){
	pid_t pid;
	int status;
	if(cmdstring == NULL){
		return 1;
	}

	if((pid = fork()) < 0){
		status = -1;
	}else if(pid == 0){		//child process
		execl("/bin/sh","sh","-c",cmdstring,(char *)0);
		_exit(127);
	}else{
		while(waitpid(pid,&status,0) < 0){
			if(errno != EINTR){
				status = -1;
				break;
			}//if
		}//while
	}
	return status;
}

static void sig_int(int signo){
	printf("caught SIGINT\n");
}

static void sig_chld(int signo){
	printf("caoght SIGCHLD\n");
}

int main(int argc,char *argv[]){
	int status;
	if(signal(SIGINT,sig_int) == SIG_ERR){
		err_sys("signal(SIGINT) error");
	}
	if(signal(SIGCHLD,sig_chld) == SIG_ERR){
		err_sys("signal(SIGCHLD) error");
	}
	if((status == my_system("/bin/ed")) < 0){
		err_sys("my_system error");
	}
	pr_exit(status);

	exit(0);
}

