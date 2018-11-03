#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	
	if(open("test1_no_umask",O_RDWR|O_CREAT|O_TRUNC,S_IROTH|S_IWOTH|S_IXOTH) < 0){
		err_sys("open error for test1_no_umask");
	}
	umask(0);
	if(open("test2_umask(0)",O_RDWR|O_CREAT|O_TRUNC,S_IROTH|S_IWOTH|S_IXOTH) < 0){
		err_sys("open error for test2_umask(0)");
	}
	exit(0);
}
