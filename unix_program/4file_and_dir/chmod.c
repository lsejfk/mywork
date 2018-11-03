#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
	struct stat buf;
	/*
	umask(0);
	if(open("test",O_RDWR|O_CREAT|O_TRUNC,S_IROTH|S_IWOTH|S_IXOTH|S_IWGRP) < 0) {
		err_sys("open error for test");
	}
	*/
	//turn on the set-group-id and turn off group-execute
	if(stat("test",&buf) < 0){
		err_sys("stat error for test");
	}
	printf("group id %d\n",buf.st_gid);
	/*
	if(chmod("test",(buf.st_mode & (~S_IWGRP)) | S_ISGID) < 0){
		err_sys("chmod error for test");
	}
	*/
	/*
	if(chmod("test",buf.st_mode | S_ISVTX) < 0){
		err_sys("chmod error for test S_ISVTX");
	}
	*/
	exit(0);
}
