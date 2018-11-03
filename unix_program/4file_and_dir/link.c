#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	struct stat buf;
	if(argc != 3){
		err_sys("usage:a.out <exist> <new>");
	}
	printf("old link:");
	if(stat(argv[1],&buf) < 0){
		err_sys("stat error for %s",argv[1]);	
	}
	printf("i-node number %ld ,number of links %ld\n",buf.st_ino,buf.st_nlink);

	if(link(argv[1],argv[2]) < 0){
		err_sys("link %s to %s error",argv[2],argv[1]);
	}

	if(stat(argv[2],&buf) < 0){
		err_sys("stat error for %s",argv[2]);
	}
	printf("new link:i-node number %ld,number of links %ld\n",buf.st_ino,buf.st_nlink);
	exit(0);
}
