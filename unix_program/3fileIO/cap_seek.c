#include "apue.h"
#include "myerr.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
		err_sys("can't seek");
	}else{
		fputs("seek ok\n",stdout);
	}
	return 0;
}
