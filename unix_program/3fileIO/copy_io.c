#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 4096

int main(){
	char buf[BUFSIZE];
	int n;
	while((n = read(STDIN_FILENO,buf,BUFSIZE)) > 0){
		if(write(STDOUT_FILENO,buf,n) != n){
			err_sys("write error");
		}
	}

	if(n < 0){
		err_sys("read error");
	}	
	exit(0);
}
