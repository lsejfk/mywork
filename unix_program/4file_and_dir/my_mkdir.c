#include "apue.h"
#include "myerr.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	int fd;
	if(argc != 2){
		err_sys("usage:a.out <pathname>");
	}
	if((fd = open(argv[1],O_RDONLY)) < 0){
		err_sys("open error for %s",argv[1]);
	}
	/*
	if(mkdir(argv[1],S_IXUSR) < 0){
		err_sys("mkdir error for %s",argv[1]);
	}
	*/
	if(rmdir(argv[1]) < 0){
		err_sys("remove failed");
	}
	sleep(20);
	exit(0);
}
