#include "apue.h"
#include "myerr.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define OPEN_MAX_GUESS 256
#ifdef OPEN_MAX
	static long openmax = OPEN_MAX
#else
	static long openmax = 0;
#endif

int duplicate(int fd,int fd2){
	int n,top;
	int *stack;
	if(openmax == 0){		//No define
		errno = 0;
		if((openmax = sysconf(_SC_OPEN_MAX)) < 0){		//error
			printf("sysconf error\n");
			return -1;	//error
		}else{
			openmax = OPEN_MAX_GUESS;
		}
	}//if

	if(fd2 > openmax || fd2 < 3){	//0,1,2
		printf("fd2 error\n");
		return -1;		//error
	}

	stack = (int *)malloc(sizeof(int) * (openmax));
	top = 0;
	
	for(n=dup(fd);n<fd2;n=dup(fd)){
		if(-1 == n){
			printf("dup error\n");
			return -1;
		}
		stack[top++] = n;
	}

	close(fd2);
	if((n = dup(fd)) == -1){
		printf("dup error\n");
		return -1;
	}else{				//success
		while(top > 0){
			close(stack[--top]);
		}
		return n;		//success
	}

}


int main(){
	int fd,fd2;
	scanf("%d%d",&fd,&fd2);
	printf("%d\n",duplicate(fd,fd2));
	exit(0);

}
