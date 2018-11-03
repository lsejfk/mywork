#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

void my_setbuf(FILE *fp,char *buf){
	if(buf == NULL){		//disable buffering
		if(setvbuf(fp,NULL,_IONBF,0) < 0){
			err_sys("setvbuf error for _IONBF");
		}
		return;
	}
	if(fp == stdin || fp == stdout || fp == stderr){	//terminal device
		if(setvbuf(fp,buf,_IOLBF,BUFSIZ) < 0){
			err_sys("setvbuf error for _IOLBF");
		}
	}else{
		if(setvbuf(fp,buf,_IOFBF,BUFSIZ) < 0){
			err_sys("setvbuf error for _IOFBF");
		}
	}
}


int main(){
	FILE *fp;
	char buf[1024];
	printf("use my_setbuf:\n");
	printf("stderr is ");
	if(stderr->_flags & _IO_UNBUFFERED){
		printf("unbuffered\n");
	}else{
		printf("not unbuffered\n");
	}
	printf("enable unbuffered file:stderr\n");
	my_setbuf(stderr,buf);
	if(stderr->_flags & _IO_LINE_BUF){
		printf("line buffer\n");
	}else{
		printf("not line buffer\n");
	}

	printf("use the stdin :\n");
	setbuf(stdin,buf);
	if(stdin->_flags & _IO_LINE_BUF){
		printf("stdin is line buffer\n");
	}else{
		printf("stdin isn't line buffer\n");
	}
	return 0;
}
