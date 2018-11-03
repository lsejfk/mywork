#include "apue.h"
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "myerr.h"

static jmp_buf env_alarm;

static void sig_alrm(int signo){
	longjmp(env_alarm,1);
}

unsigned int sleep2(unsigned int seconds){
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		return seconds;
	}
	if(setjmp(env_alarm) == 0){
		alarm(seconds);
		pause();
	}
	return alarm(0);
}

static void sig_int(int signo){
	int i,j;
	volatile int k;

	printf("\nsig_int starting\n");
	for(i=0;i<300000;i++){
		for(j=0;j < 4000;j++){
			k += i * j;
		}
	}
	printf("sig_int finished\n");
}

int main(void){
	unsigned int unslept;
	if(signal(SIGINT,sig_int) == SIG_ERR){
		err_sys("signal error");
	}
	unslept = sleep2(5);
	printf("sleep 2 returned:%u\n",unslept);
	exit(0);
}
