#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>

int globvar = 6;

int main(){
	int var;
	pid_t pid;

	var = 88;

	printf("before fork\n");

	if((pid = vfork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){	//child process
		globvar++;
		var++;
		exit(0);
	}else{			//parent process
		sleep(2);
	}

	printf("pid= %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);
	exit(0);
}
