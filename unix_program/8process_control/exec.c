#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char *env_init[] = { "USER=michael","PATH=/home/michael/learnfile/unix_program/8process_control/","LD_LIBRARY_PATH=/home/michael/local/src/",NULL};

int main(){
	pid_t pid;

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		sleep(2);
		if(execle("write","write","the first arg\n","write the second arg\n",(char *)0,env_init) < 0){
			err_sys("execle error");
		}
	}

	if(waitpid(pid,NULL,0) < 0){
		err_sys("wait error");
	}
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		if(execle("read","read","temp.test",(char *)0,env_init) < 0){
			err_sys("execlp error");
		}
	}
	exit(0);
}
