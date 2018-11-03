#include "apue.h"
#include "myerr.h"
#include <unistd.h>

int main(){
	pid_t pid,gid;
	if(setpgid(getpid(),1000) < 0){
		err_sys("setpgid error");
	}
	if((pid = fork()) < 0){
		err_sys("fork error");
	}
	printf("the process id=%ld,the group id=%ld\n",getpid(),getpgrp());
	return 0;
}
