#include "apue.h"
#include "myerr.h"
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096

int main(int argc,char *argv[]){
	int fdr,fdw;
	int n;
	char buf[BUFSIZE];
	struct stat statbuf;
	if(argc != 3){
		err_sys("usage:a.out <file1> <copyfile>");
	}
	if((fdr = open(argv[1],O_RDONLY)) < 0){
		err_sys("open error for %s",argv[1]);
	}
	if(fstat(fdr,&statbuf) < 0){
		err_sys("fstat error for fd %d",fdr);
	}
	umask(0);
	if((fdw = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,statbuf.st_mode)) < 0){
		err_sys("open error %s",argv[2]);
	}
	while((n = read(fdr,buf,BUFSIZE)) > 0){
		if(write(fdw,buf,n) != n){
			err_sys("write error");
		}
	}
	if(n < 0){
		err_sys("read error");
	}
	
	exit(0);
}
