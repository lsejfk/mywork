#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <errno.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

#define PATH_MAX_GUESS 1024

char *path_alloc(size_t *size){
	long posix_version,xsi_version;
	char *ptr;
	long t;
	posix_version = xsi_version = 0;
	posix_version = sysconf(_SC_VERSION);
	xsi_version = sysconf(_SC_XOPEN_VERSION);

	if(pathmax == 0){
		errno = 0;
		if((pathmax = pathconf("/",_PC_PATH_MAX)) < 0){
			if(errno == 0){
				pathmax = PATH_MAX_GUESS;
			}else{
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}else{
			pathmax++;
		}
	}

	if(posix_version < 200112L && xsi_version < 4){
		t = pathmax + 1;
	}else{
		t = pathmax;
	}
	if((ptr = malloc(*size)) == NULL){
		err_sys("malloc failed");
	}
	if(size != NULL){
		*size = t;
	}
	return ptr;
}

int main(int argc,char *argv[]){
	/*
	if(chdir("/tmp") < 0){
		err_sys("chdir error for /tmp");
	}
	printf("chdir to /tmp successed\n");
	*/
	char *ptr;
	size_t size;
	if(chdir("/tmp") < 0){
		err_sys("chdir failed");
	}
	ptr = path_alloc(&size);
	if(getcwd(ptr,size) == NULL){
		err_sys("getcwd failed");
	}
	printf("cwd=%s\n",ptr);
	exit(0);
}
