#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef _POSIX_CHOWN_RESTRICTED
int main(){
	if(chown("test",-1,1000) < 0){
		err_sys("chown error for test");
	}
	exit(0);
}
#endif
