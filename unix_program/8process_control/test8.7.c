#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <dirent.h>

int main(){
	pid_t pid;
	int fd;
	DIR *dirp;
	struct dirent *dp;
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		if((dirp = opendir("/")) == NULL){
			err_sys("opendir error");
		}

		if(execlp("ls","ls","-al",(char *)0) < 0){
			err_sys("execl error");
		}
		while((dp = readdir(dirp)) != NULL){
			printf("%s\n",dp->d_name);
		}
		exit(0);
	}
	if(wait(NULL) < 0){
		err_sys("wait error");
	}
	exit(0);
}
