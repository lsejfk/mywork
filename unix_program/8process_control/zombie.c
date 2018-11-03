#include "apue.h"
#include "myerr.h"
#include <sys/wait.h>

int main(){
	pid_t pid;
	int flag = 0;

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){		//child process
		flag = 1;
		printf("first child flag = %d\n",flag);
		if((pid = fork()) < 0){
			err_sys("fork error");
		}else if(pid > 0){	
			exit(0);
		}else{
			//the second child process
			printf("second child,parent pid = %ld\n",(long)getppid());
			printf("second child,pid = %ld\n",(long)getpid());
			printf("second child flag = %d\n",flag);
			exit(0);
		}
	}

	printf("hello world\n");
	if(waitpid(pid,NULL,0) < 0){
		err_sys("waitpid error");
	}
	printf("parent process terminate\n");
	printf("parent process flag= %d\n",flag);
	exit(0);
}
