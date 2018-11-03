#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_abort(int signo){
	printf("catch the SIGABRT\n");
}

int main(){
	sigset_t newsig;
	struct sigaction sigabort,oldsig;
	sigabort.sa_handler = sig_abort;
	sigemptyset(&sigabort.sa_mask);
	sigabort.sa_flags = 0;
	if(sigaction(SIGABRT,&sigabort,&oldsig) < 0){
		err_sys("sigaction error");
	}

	printf("call abort:\n");
	abort();
	exit(0);
}
