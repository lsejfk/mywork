#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	pid_t pid;
	char bufp[] = "this is parent process\n";
	char bufc[] = "this is child process\n";
	int fd;

	if((fd = open("temp.out",O_RDWR)) < 0){
		err_sys("failed open %s","temp.out");
	}

	if(write(fd,bufp,sizeof(bufp)-1) != sizeof(bufp)-1){
		err_sys("write error");
	}
	printf("write into parent process\n");

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){		//child process
		if(write(fd,bufc,sizeof(bufc)-1) != sizeof(bufc)-1){
			err_sys("write error in child process");
		}
		printf("write into child process\n");
	}else{
		printf("wait for 5 seconds\n");
		sleep(5);
		if(write(fd,"the end",7) != 7){
			err_sys("write error in parent process");
		}
		printf("write the end into parent process success\n");
	}
	close(fd);
	exit(0);
}
