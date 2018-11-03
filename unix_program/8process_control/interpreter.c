#include <stdio.h>
#include "apue.h"
#include "myerr.h"
#include <sys/wait.h>
#include <unistd.h>


int main(){
	pid_t pid;
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){	//child process
		if(execl("/home/michael/learnfile/perl/5inputOutput/printf",(char *)0) < 0){
			err_sys("execl error");
		}
		exit(0);
	}
	if(waitpid(pid,NULL,0) < 0){
		err_sys("waitpid error");
	}
	printf("parent process:child process finished\n");
	exit(0);
}
