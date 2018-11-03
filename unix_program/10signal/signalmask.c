#include "apue.h"
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;

	if(sigprocmask(0,NULL,&sigset) < 0){
		err_ret("sigprocmask error");
	}else{
		printf("%s",str);
		if(sigismember(&sigset,SIGINT)){
			printf(" SIGINT");
		}
		if(sigismember(&sigset,SIGQUIT)){
			printf(" SIGQUIT");
		}
		if(sigismember(&sigset,SIGUSR1)){
			printf(" SIGUSR1");
		}
		if(sigismember(&sigset,SIGALRM)){
			printf(" SIGALRM");
		}
		printf("\n");
	}
	errno = errno_save;
}

static void sig_quit(int);

int main(){
	sigset_t newmask,oldmask,pendmask,fillmask;

	if(signal(SIGINT,sig_quit) == SIG_ERR){
		err_sys("can't catchSIGQUIT");
	}

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	pr_mask("current signal mask:\n");
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0){
		err_sys("SIG_BlOCK error");
	}
	pr_mask("after block SIGQUIT:\n");
	sigemptyset(&pendmask);
	sigaddset(&pendmask,SIGQUIT);
	if(sigsuspend(&pendmask) != -1){
		err_sys("sigsuspend error");
	}
	pr_mask("after sigsuspend\n");
	sigfillset(&fillmask);
	if(sigprocmask(SIG_SETMASK,&fillmask,NULL) < 0){
		err_sys("sigprocmask error");
	}
	pr_mask("after sigprocmask fillmask:");
	/*
	sleep(5);

	if(sigpending(&pendmask)){
		err_sys("SIG_SETMASK error");
	}
	if(sigismember(&pendmask,SIGQUIT)){
		printf("\nSIGQUIT pending\n");
	}

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){
		err_sys("SIG_SETMASK error");
	}
	printf("SIGQUIT unblocked\n");
	pr_mask("after unblocked:\n");
	sleep(5);
	*/
	exit(0);
}

static void sig_quit(int signo){
	printf("caught SIGINT\n");
	pr_mask("sig_quit:\n");
	/*
	if(signal(SIGQUIT,SIG_DFL) == SIG_ERR){
		err_sys("can't reset SIGQUIT");
	}
	*/
}
