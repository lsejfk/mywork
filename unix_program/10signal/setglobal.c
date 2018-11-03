#include "apue.h"
#include "myerr.h"
#include <signal.h>
#include <unistd.h>
static void sig_proc(int signo);

volatile sig_atomic_t quitflag = 0;

int main(){
	sigset_t newsig,oldsig,cursig;

	if(signal(SIGQUIT,sig_proc) == SIG_ERR){
		err_sys("signal(SIGQUIT) error");
	}
	if(signal(SIGINT,sig_proc) == SIG_ERR){
		err_sys("signal(SIGINT) error");
	}

	sigemptyset(&newsig);
	sigemptyset(&cursig);
	sigaddset(&newsig,SIGQUIT);

	if(sigprocmask(SIG_BLOCK,&newsig,&oldsig) < 0){
		err_sys("sigprocmask error");
	}

	while(quitflag == 0){
		sigsuspend(&cursig);
	}
	quitflag = 0;

	if(sigprocmask(SIG_SETMASK,&oldsig,NULL) < 0){
		err_sys("sigprocmask error");
	}
	return 0;
}

static void sig_proc(int signo){
	if(signo == SIGQUIT){
		quitflag = 1;
	}else if(signo == SIGINT){
		printf("\n in interrupt\n");
	}
}
