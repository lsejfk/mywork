#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
static void sig_alrm(int signo){
	printf("caught SIGALRM\n");
}

int main(){
	struct sigaction theact,oldact;
	FILE *fp;
	double te[100001];
	theact.sa_handler = sig_alrm;
	theact.sa_flags = 0;
	sigemptyset(&theact.sa_mask);

	if(sigaction(SIGALRM,&theact,&oldact) < 0){
		err_sys("sigaction error");
	}
	if((fp = fopen("byte","a+")) == NULL){
		err_sys("fopen error");
	}
	alarm(1);
	if(fwrite(&te[0],sizeof(double),100001,fp) != 100001){
		err_sys("fwrite error");
	}
	printf("complete\n");

	exit(0);
}
