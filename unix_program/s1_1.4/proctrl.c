#include "apue.h"
#include "myerr.h"
#include<sys/wait.h>

static void sig_int(int);

int main(){
	pid_t pid;
	char buf[MAXLINE];
	int status;

	if(signal(SIGINT,sig_int) == SIG_ERR){
		err_sys("signal error");
	}

	while(fgets(buf,MAXLINE,stdin) != NULL){
		if(buf[strlen(buf)-1] == '\n'){
			buf[strlen(buf)-1] = '\0';
		}

		if((pid = fork()) < 0){
			err_sys("fork error");
		}else if(pid == 0){
			execlp(buf,buf,(char *)0);
			err_ret("couldn't execute :%s",buf);
			exit(127);
		}

		printf("parent process id:%ld\n",(long)getpid());
		printf("child process id :%ld\n",(long)pid);

		if((pid = waitpid(pid,&status,0)) < 0){
			err_sys("waitpid error");
		}
		printf("%%");
	}
	exit(0);
}


void sig_int(int signo){
	printf("interrupt \n%% ");
}

