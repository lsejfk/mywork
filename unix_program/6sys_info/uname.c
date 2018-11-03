#include "apue.h"
#include "myerr.h"
#include <sys/utsname.h>

int main(){
	struct utsname sys;
	if(uname(&sys) < 0){
		err_sys("uname error");
	}
	printf("sysname:%s\nnodename:%s\nrelease:%s\nversion:%s\nmechine:%s\n",
		sys.sysname,sys.nodename,sys.release,sys.version,sys.machine);
	return 0;
}
