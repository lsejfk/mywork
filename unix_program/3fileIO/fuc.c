#include <fcntl.h>
#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int main(){
	int fd,fd2;
	long e;
	off_t curpos;
	ssize_t cu;
	char buf[4096];
	if((fd = open("file.hole",O_RDWR|O_APPEND)) < 0){
		err_sys("open file.hole error");
	}

	curpos = lseek(fd,0,SEEK_CUR);
	printf("%d\n",curpos);
	curpos = lseek(fd,-5,SEEK_END);
	printf("%d\n",curpos);
	if((cu = write(fd,"replace",7)) != 7){
		err_sys("write %d error",fd);
	}
	/*
	if((cu = read(fd,buf,5)) < 0){
		err_sys("read %d error",fd);
	}
	printf("%s\n",buf);
	*/
	/*
	if((fd = open("./file.hole",O_RDWR)) < 0){
		err_sys("open file.hole failed");
	}
	if((fd2 = dup(fd)) < 0){
		err_sys("dup error");
	}
	printf("fd=%d,fd2=%d\n",fd,fd2);
	if((fd2 = dup2(fd,fd2)) < 0){
		err_sys("dup2 error");
	}
	printf("fd2 = %d\n",fd2);
	if((fd2 = dup2(fd2,fd2)) < 0){
		err_sys("dup2 error");
	}
	printf("fd2=%d\n",fd2);
	*/
	/*
	if((cu = read(fd,buf,5)) < 0){
		err_sys("read error");
	}
	printf("size=%d,%s\n",cu,buf);
	*/
	/*
	if((cu = read(fd,buf,100)) < 0){
		err_sys("read error");
	}
	printf("size=%d,%s\n",cu,buf);

	curpos = lseek(fd,5,SEEK_SET);
	printf("curpos=%ld\n",curpos);

	if((cu = write(fd,"hello world",11)) < 0){
		err_sys("write error");
	}
	curpos = lseek(fd,0,SEEK_CUR);
	printf("curpos = %ld\n",curpos);
	*/
	/*
	if((cu = read(STDIN_FILENO,buf,100)) < 0){
		err_sys("read error");
	}
	printf("size=%d,%s\n",cu,buf);
	*/	
	/*
	if((e = sysconf(_SC_V7_ILP32_OFF32)) >= 0){
		printf("1_%ld\n",e);
	}else if((e = sysconf(_SC_V7_ILP32_OFFBIG)) >= 0 ){
		printf("2_%ld\n",e);
	}else if((e = sysconf(_SC_V7_LP64_OFF64)) >= 0){
		printf("3_%ld\n",e);
	}
	*/
	/*jjjjjjjjjjjjjjjjjjjjjj

	if((fd = open("./file.hole",O_RDONLY|O_TRUNC)) < 0){
		err_sys("open failed");
	}
	printf("%d\n",fd);

	if((fd = openat(AT_FDCWD,"../s1_1.4/",O_RDONLY)) < 0){
		err_sys("openat failed");
	}
	printf("%d\n",fd);
	if((fd = openat(fd,"ls1.c",O_RDONLY)) < 0){
		err_sys("openat failed fd");
	}
	printf("%d\n",fd);

	printf("%d\n",	NAME_MAX);
	
	errno = 0;
	if((e = pathconf("sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss",_PC_NO_TRUNC) < 0)){
		if(errno){
			err_sys("error");
		}
	}

	printf("%ld\n",e);
	*/
	/*
	if((fd = open("./file.hole",O_RDWR)) < 0){
		err_sys("open rdwr failed");
	}
	printf("%d\n",fd);
	*/
	/*

	if((fd = open("file.hole",O_RDONLY)) < 0){
		err_sys("open file.hole failed");
	}
	
	curpos = lseek(fd,0,SEEK_CUR);
	printf("%ld\n",curpos);
	curpos = lseek(fd,9,SEEK_SET);
	printf("%ld\n",curpos);
	curpos = lseek(fd,-2,SEEK_END);
	printf("%ld\n",curpos);
	curpos = lseek(fd,2,SEEK_CUR);
	printf("%ld\n",curpos);
	*/

	exit(0);
}
