#include "apue.h"
#include "myerr.h"
#include <sys/wait.h>
#include <stdio.h>

int main(){
	pid_t pid;
	int status;

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){		//child
		exit(7);
	}

	if(wait(&status) != pid){
		err_sys("wait error");
	}
	pr_exit(status);

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		abort();		//generates SIGABRT
	}

	if(wait(&status) != pid){
		err_sys("wait error");
	}
	pr_exit(status);

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		status /= 0;
	}

	if(wait(&status) != pid){
		err_sys("wait error");
	}
	pr_exit(status);
	exit(0);
}
