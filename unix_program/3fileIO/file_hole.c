#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";
	char buf[16384];
	int fd,i;

	for(i=0;i<16384;i++){
		buf[i] = 'a';
	}

	if((fd = creat("file.nohole",FILE_MODE)) < 0){
		err_sys("create error");
	}

	if(write(fd,buf1,10) != 10){
		err_sys("buf1 write error");
	}

	if(write(fd,buf,16384) != 16384){
		err_sys("buf wirte error");
	}

	if(write(fd,buf2,10) != 10){
		err_sys("buf2 write error");
	}
	exit(0);
}
