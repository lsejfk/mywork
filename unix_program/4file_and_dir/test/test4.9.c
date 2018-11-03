#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <fcntl.h>

int main(){
	/*
	if(link("/tmp/test","./test1") < 0){
		err_sys("link error:/tmp/test to ./test1");
	}
	*/
	if(unlink("./test1") < 0){
		err_sys("unlink error for ./test1");
	}
	printf("unlink success\n");
	exit(0);
}
