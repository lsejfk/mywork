#include "apue.h"
#include "myerr.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	if(argc != 3){
		err_sys("usage:a.out <oldname> <newname>");
	}
	if(rename(argv[1],argv[2]) < 0){
		err_sys("rename error for %s to %s",argv[1],argv[2]);
	}
	exit(0);
}
