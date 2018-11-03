#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>


int main(int argc,char *argv[]){
	int i;
	struct stat statbuf;
	for(i=1;i<argc;i++){
		if(stat(argv[i],&statbuf) < 0){
			err_ret("stat error for %s",argv[i]);
			continue;
		}
		printf("%s:dev=%d/%d",argv[i],major(statbuf.st_dev),minor(statbuf.st_dev));
		if(S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)){
			printf("(%s) rdev=%d/%d\n",S_ISCHR(statbuf.st_mode) ? "character" : "block",major(statbuf.st_rdev),minor(statbuf.st_rdev));
		}
		printf("\n");
	}
	exit(0);
}
