#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	/*
	if(argc != 3){
		err_sys("usage:a.out <actualpath> <newpath>");
	}
	if(symlink(argv[1],argv[2]) < 0){
		err_sys("symlink error for %s to %s",argv[1],argv[2]);
	}
	*/
	ssize_t bs;
	char buf[4096];
	size_t bufsize;
	if(argc != 2){
		err_sys("usage:a.out <pathname>");
	}
	if((bs = readlink(argv[1],buf,100)) < 0){
		err_sys("readlink error for %s",argv[1]);
	}
	printf("size=%ld,%s\n",bs,buf);
	exit(0);
}
