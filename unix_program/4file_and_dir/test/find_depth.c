#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc,char *argv[]){
	int i;
	char *fullpath;
	long pathmax,n;
	int depth = 0;
	pathmax = PATH_MAX;
	fullpath = (char *)malloc(pathmax);
	if(fullpath == NULL){
		err_sys("malloc error");
	}
	if(argc != 2){
		err_sys("usage:a.out <number>");
	}
	printf("PATH_MAX=%ld\n",pathmax);
	if((fullpath = getcwd(fullpath,pathmax)) == NULL){
		err_sys("getcwd error");
	}
	for(i=0;i<atoi(argv[1]);i++){
		n = strlen(fullpath);
		if(n + NAME_MAX + 2 > pathmax){
			pathmax *= 2;
			if((fullpath = (char *)realloc(fullpath,pathmax)) == NULL){
				err_sys("realloc error");
			}
		}
		if((fullpath = getcwd(fullpath,pathmax)) == NULL){
			err_sys("getcwd error");
		}
		if(mkdir("hello",S_IWUSR|S_IXUSR|S_IRUSR) < 0){
			printf("depth=%d,path:%s\n",depth,fullpath);
			err_sys("mkdir error for %s",fullpath);
		}
		if(chdir("hello") < 0){
			printf("depth=%d,path:%s\n",depth,fullpath);
			err_sys("chdir error for %s",fullpath);
		}
		depth++;
	}

}
