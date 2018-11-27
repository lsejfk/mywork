#include <strings.h>
#include "apue.h"
#include "myerr.h"
#include "unp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
static void cli_echo(FILE *fp,int connfd);

int main(int argc,char *argv[]){
	struct sockaddr_in cliaddr;
	int connfd;
	if(argc != 2){
		err_quit("usage:a.out <IPaddress>");
	}
	if((connfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
		err_sys("socket() error");
	}
	bzero((void *)&cliaddr,sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = SERV_PORT;
	if(inet_pton(AF_INET,argv[1],&cliaddr.sin_addr.s_addr) < 0){
		err_sys("inet_pton() error");
	}
	if(connect(connfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr)) < 0){
		err_sys("connet() error");
	}
	cli_echo(stdin,connfd);
	exit(0);
}

static void cli_echo(FILE *fp,int connfd){
	char recbuf[MAXLINE],sendbuf[MAXLINE];
	while(fgets(sendbuf,MAXLINE,fp) != NULL){
		if(writen(connfd,sendbuf,strlen(sendbuf)) != strlen(sendbuf)){
			err_sys("writen error");
		}
		if(readline(connfd,recbuf,MAXLINE) == 0){
			err_sys("cli_echo:server terminated prematurely");
		}
		fputs(recbuf,stdout);
	}
}
