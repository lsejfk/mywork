#include "unp.h"
#include "myerr.h"

int main(int argc,char *argv[]){
	int sockfd,n,counter;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr,*locaddr_in;
	socklen_t len;
	struct sockaddr localaddr;
	char buff[MAXLINE];

	if(argc != 2){
		err_quit("usage:a.out <ip address>");
	}
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		err_sys("socket error");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0){
		err_quit("inet_pton error for %s",argv[1]);
	}
	if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr)) < 0){
		err_sys("connect error");
	}
	len = sizeof(localaddr);
	if(getsockname(sockfd,&localaddr,&len) < 0){
		err_sys("getsockname error");
	}
	locaddr_in = (struct sockaddr_in *)&localaddr;
	printf("ip:%s,port:%d\n",inet_ntop(AF_INET,&locaddr_in->sin_addr.s_addr	,buff,sizeof(buff)),ntohs(locaddr_in->sin_port));
	counter = 0;
	while((n = read(sockfd,recvline,MAXLINE)) > 0){
		recvline[n] = '\0';
		counter++;
		printf("counter=%d\n",counter);
		if(fputs(recvline,stdout) == EOF){
			err_sys("fputs error");
		}
	}
	if(n < 0){
		err_sys("read error");
	}
	exit(0);
}
