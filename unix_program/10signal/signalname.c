#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
	char buf[4096];
	psignal(SIGINT,"SIGINT info:");
	printf("srsignal:%s\n",strsignal(SIGQUIT));
	exit(0);
}
