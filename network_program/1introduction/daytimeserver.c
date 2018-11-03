#include "unp.h"
#include <time.h>

int main(int argc,char *argv[]){
	int listenfd,connfd,n;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	char *p;
	time_t ticks;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		fprintf(stderr,"socket error");
		exit(-1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);

	if(bind(listenfd,(SA *)&servaddr,sizeof(servaddr)) < 0){
		fprintf(stderr,"bind error");
		exit(-1);
	}
	if(listen(listenfd,LISTENQ) < 0){
		fprintf(stderr,"listen error");
		exit(-1);
	}

	for(;;){
		if((connfd = accept(listenfd,(SA *)NULL,NULL)) < 0){
			fprintf(stderr,"accept error");
			exit(-1);
		}
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		p = buff;
		while(*p){
			if((n = write(connfd,p,1)) != 1){
				fprintf(stderr,"write error");
				exit(-1);
			}
			++p;
		}

		if(close(connfd) < 0){
			fprintf(stderr,"close error");
			exit(-1);
		}
	}
}
