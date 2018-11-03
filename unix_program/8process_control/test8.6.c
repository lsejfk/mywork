#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int status;
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		printf("child process\n");
		if((status = system("ps")) < 0){
			err_sys("system() error");
		}
		pr_exit(status);
		exit(0);
	}
	if(wait(&status) < 0){
		err_sys("wait error");
	}
	printf("child process finished\n");
	exit(0);
}
