#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void print_ids(char *name){
	printf("%s:pid=%ld,ppid=%d,gid=%ld,sid=%ld,pgrpid=%ld\n",
		name,(long)getpid(),(long)getppid(),(long)getpgrp(),(long)getsid(0),(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(){
	pid_t pid;
	pid_t sid;
	print_ids("parent");
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){	//child
		print_ids("child");
		if((sid = setsid()) < 0){
			err_sys("setsid error");
		}
		print_ids("child");
	}

}
