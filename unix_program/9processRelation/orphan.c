#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

static void sig_hup(int signo){
	printf("SIGHUP received,pid= %ld\n",(long)getpid());
}

static void pr_ids(char *name){
	printf("%s:pid=%ld,ppid=%ld,pgrp=%ld,tpgrp=%ld\n",name,(long)getpid(),(long)getppid(),(long)getpgrp(),(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(){
	char c;
	pid_t pid;
	pr_ids("parents");
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){
		sleep(5);
	}else{
		pr_ids("child");
		signal(SIGHUP,sig_hup);
		kill(getpid(),SIGTSTP);
		pr_ids("child");
		if(read(STDIN_FILENO,&c,1) != 1){
			printf("read error %d on controlling tty\n",errno);
		}
	}
	exit(0);
} 
