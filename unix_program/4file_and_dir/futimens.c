#include "apue.h"
#include "myerr.h"
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	int i,fd;
	struct stat statbuf;
	struct timespec times[2];

	for(i=1;i<argc;i++){
		if(stat(argv[i],&statbuf) < 0){
			err_ret("%s:stat error",argv[i]);
			continue;
		}
		if((fd = open(argv[i],O_RDWR|O_TRUNC)) < 0){
			err_ret("%s:open error",argv[i]);
			continue;
		}
		times[0] = statbuf.st_atim;
		times[1] = statbuf.st_mtim;
		times[0].tv_nsec = UTIME_NOW;
	
		if(futimens(fd,times) < 0){
			err_ret("%s:futimens error",argv[i]);
		}
	}//for
	exit(0);
}
