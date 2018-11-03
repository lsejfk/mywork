#include <sys/param.h>
#include "apue.h"
#include "myerr.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/resource.h>

#ifdef OPEN_MAX
	static long openmax = OPEN_MAX;
#else
	static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(){
	struct rlimit rt;
	if((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX){
		if(getrlimit(RLIMIT_NOFILE,&rt) < 0){
			err_sys("can't get the file limit");
		}
		if(rt.rlim_max == RLIM_INFINITY){
			openmax = OPEN_MAX_GUESS;
		}else{
			openmax = rt.rlim_max;
		}
	}
	return openmax;
}


int main() {
	printf("%ld\n",open_max());
	printf("%d\n",NOFILE);
	return 0;
}
