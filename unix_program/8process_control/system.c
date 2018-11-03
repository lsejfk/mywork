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
}

int main(){
	int status;
	if((status == my_system("date")) < 0){
		err_sys("my_system error");
	}
	pr_exit(status);

	if((status == my_system("ls")) < 0){
		err_sys("my_system error");
	}
	pr_exit(status);

	if((status = my_system("nosuchcommand")) < 0){
		err_sys("my_system error");
	}	
	pr_exit(status);

	if((status = my_system("who;exit 44")) < 0){
		err_sys("my_system error");
	}
	pr_exit(status);
	exit(0);
}

