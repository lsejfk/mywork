#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <signal.h>

#define BUFFSIZE 1024

static void sig_tstp(int signo){
	sigset_t mask;
	struct sigaction act_tstp;

	act_tstp.sa_flags = 0;
	sigemptyset(&act_tstp.sa_mask);


	sigemptyset(&mask);
	sigaddset(&mask,SIGTSTP);
	if(sigprocmask(SIG_UNBLOCK,&mask,NULL) < 0){
		err_sys("sigprocmask error");
	}
	act_tstp.sa_handler = SIG_DFL;
	if(sigaction(SIGTSTP,&act_tstp,NULL) < 0){
		err_sys("sigaction error");
	}
	kill(getpid(),SIGTSTP);

	act_tstp.sa_handler = sig_tstp;
	if(sigaction(SIGTSTP,&act_tstp,NULL) < 0){
		err_sys("sigaction error");
	}
}

int main(){
	int n;
	char buf[BUFFSIZE];
	struct sigaction act_tstp;

	if(sigaction(SIGTSTP,NULL,&act_tstp) < 0){
		err_sys("sigaction error");
	}
	if(act_tstp.sa_handler == SIG_DFL){
		act_tstp.sa_handler = sig_tstp;
		sigaction(SIGTSTP,&act_tstp,NULL);
	}

	while((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0){
		if(write(STDOUT_FILENO,buf,n) != n){
			err_sys("write error");
		}
	}
	if(n < 0){
		err_sys("read error");
	}

	exit(0);
}
