#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
	printf("%s\n",strsignal(SIGKILL));
	printf("%s\n",_sys_siglist[SIGKILL]);
	exit(0);
}
