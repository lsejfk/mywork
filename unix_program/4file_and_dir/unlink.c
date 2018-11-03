#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	if(open("/tmp/hel/data",O_RDWR) < 0){
		err_sys("open error for data");
	}
	if(unlink("/tmp/hel/data") < 0){
		err_sys("unlink error for data");
	}
	printf("unlinked data\n");
	sleep(15);
	printf("done\n");
	/*
	if(unlink("/tmp/hel/data") < 0){
		err_sys("unlink error for /tmp/test.data");
	}
	*/
	
	exit(0);
}
