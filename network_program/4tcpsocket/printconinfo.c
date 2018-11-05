#include "unp.h"
#include "apue.h"
#include "myerr.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

int main(){
	int listendfd,clfd;
	struct sockaddr_in servaddr,clienaddr,*locaddr_in;
	struct sockaddr localaddr;
	char buff[MAXLINE],ipaddr[INET_ADDRSTRLEN + 1];
	char *ptr;
	socklen_t len;

	if((listendfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
		err_sys("socket error");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
/*

	if(bind(listendfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
		err_sys("bind error");
	}
*/

	if(listen(listendfd,LISTENQ) < 0){
		err_sys("listen error");
	}
	len = sizeof(localaddr);
	if(getsockname(listendfd,&localaddr,&len) < 0){
		err_sys("getsockname error");
	}
	locaddr_in = (struct sockaddr_in *)&localaddr;
	printf("ip:%s,port:%d\n",inet_ntop(AF_INET,&locaddr_in->sin_addr.s_addr	,buff,sizeof(buff)),ntohs(locaddr_in->sin_port));

	for(;;){
		len = sizeof(clienaddr);
		if((clfd = accept(listendfd,(struct sockaddr *)&clienaddr,&len)) < 0){
			err_sys("accept error");
		}
		snprintf(buff,sizeof(buff),"connetion:ip %s,port %d\n",inet_ntop(AF_INET,&clienaddr.sin_addr.s_addr,ipaddr,sizeof(ipaddr)),ntohs(clienaddr.sin_port));
		if(write(clfd,buff,strlen(buff)) != strlen(buff)){
			err_sys("write error");
		}
		if(close(clfd) < 0){
			err_sys("close error");
		}
	}
	exit(0);
}
