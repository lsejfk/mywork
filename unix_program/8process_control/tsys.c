#include "apue.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	int status;
	if(argc < 2){
		printf("command line arguement required\n");
		exit(-1);
		//err_quit("command line arguement required");
	}
	if((status == system(argv[1])) < 0){
		fprintf(stderr,"system error");
		exit(-1);
		//err_sys("system error");
	}
//	pr_exit(status);
	exit(0);
}
