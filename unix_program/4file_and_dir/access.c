#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
	int fd;
	if(argc != 2){
		err_quit("usage:a.out <pathname>");
	}
	if((fd = open(".",O_RDONLY)) < 0){
		err_sys("open error for .");
	}
	if(access(argv[1],R_OK) < 0){
		err_ret("faccess error for %s",argv[1]);
	}else{
		printf("read access ok\n");
	}

	if(open(argv[1],O_RDONLY) < 0){
		err_ret("open error for %s",argv[1]);
	}else{
		printf("open for reading OK\n");
	}
	exit(0);
}
