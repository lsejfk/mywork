#include "unp.h"
#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

static void str_echo(int connfd);
static void sig_chld(int signo){
     int stat;
     pid_t pid;

     pid = wait(&stat);
     printf("child %d terminated\n",pid);
}

int main(){
	pid_t pid;
	int listenfd,connfd;
	struct sockaddr_in socketaddr,clientaddr;
     struct sigaction act,oact;
	socklen_t clienlen;

	if((listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
		err_sys("socket() error");
	}
	bzero(&socketaddr,sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = SERV_PORT;
	socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd,(struct sockaddr *)&socketaddr,sizeof(socketaddr)) < 0){
		err_sys("bind() error");
	}

	if(listen(listenfd,LISTENQ) < 0){
		err_sys("listen() error");
	}
     act.sa_handler = sig_chld;
     sigemptyset(&act.sa_mask);
     act.sa_flags = 0;
     if(sigaction(SIGCHLD,&act,&oact) < 0){
          err_sys("sigaction error");
     }
	for(;;){
		clienlen = sizeof(struct sockaddr_in);
		if((connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clienlen)) < 0){
			err_sys("accept() error");
		}
		if((pid = fork()) == 0){	//child process
			if(close(listenfd) < 0){
				err_sys("close() error");
			}
			str_echo(connfd);
			exit(0);
		}
		if(close(connfd) < 0){
			err_sys("close() error");
		}
	}
	
}

static void str_echo(int connfd){
	char receivebuf[MAXLINE];
	ssize_t n;
	again:
	while((n = read(connfd,receivebuf,MAXLINE)) > 0){
		if(writen(connfd,receivebuf,n) != n){
			err_sys("write error");
		}
	}
	if(n < 0 && errno == EINTR){
		goto again;
	}else if(n < 0){
		err_sys("read error");
	}
}
