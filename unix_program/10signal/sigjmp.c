#include "apue.h"
#include <setjmp.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjmp;

static Sigfunc *mysignal(int signo,Sigfunc *func){
	struct sigaction act,oact;
	act.sa_handler = func;
	if(sigemptyset(&act.sa_mask) < 0){
		err_sys("sigemptyset error");
	}
	act.sa_flags = 0;
	if(signo == SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}else{
		act.sa_flags |= SA_RESTART;
	}

	if(sigaction(signo,&act,&oact) < 0){
		return SIG_ERR;
	}
	return oact.sa_handler;
}

static void pr_mask(char *str){
	sigset_t oset;
	int errno_save;
	printf("%s",str);
	errno_save = errno;
	if(sigprocmask(0,NULL,&oset) < 0){
		err_sys("sigprocmask error");
	}
	if(sigismember(&oset,SIGALRM)){
		printf(" SIGALRM");
	}
	if(sigismember(&oset,SIGUSR1)){
		printf(" SIGUSR1");
	}
	errno = errno_save;
}

int main(){
	if(mysignal(SIGUSR1,sig_usr1) == SIG_ERR){
		err_sys("signal SIGUSR1 error");
	}
	if(mysignal(SIGALRM,sig_alrm) == SIG_ERR){
		err_sys("signal SIGALRM error");
	}

	pr_mask("starting main:");
	if(sigsetjmp(jmpbuf,1)){
		pr_mask("ending main:");
		exit(0);
	}
	canjmp = 1;
	for(;;){
		pause();
	}
}

static void sig_usr1(int signo){
	time_t starttime;
	if(canjmp == 0){
		return;
	}
	pr_mask("in sig_usr1:");
	alarm(3);
	starttime = time(NULL);
	for(;;){
		if(time(NULL) > starttime + 5){
			break;
		}
	}
	pr_mask("sig_usr1 finished:");
	canjmp = 0;
	siglongjmp(jmpbuf,1);
}

static void sig_alrm(int signo){
	pr_mask("in sig_alrm:");
}
