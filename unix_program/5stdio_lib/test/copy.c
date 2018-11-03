#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4

int main(){
	
	/*
	char buf[MAX_LINE];
	while(gets(buf) != NULL){
		if(fputs(buf,stdout) == EOF){
			err_sys("fputs error");
		}
	}
	if(ferror(stdin)){
		err_sys("fgets error");
	}
	*/
	printf("%d\n",printf(""));
}
