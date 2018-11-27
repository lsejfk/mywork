#include "apue.h"
#include "myerr.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int flag = 0;
struct pthread_args{
	char *s;
	int *autovar;
	int fd;
};

void print_thread_id(const char *s){
	pthread_t pthid;
	pid_t pid;
	pid = getpid();
	pthid = pthread_self();
	printf("%s pid %lu thread id %lu  (0x%lx)\n",s,(unsigned long)pid,pthid,pthid);
}

void * thr_fn(void *arg){
	struct pthread_args *rargs;
	char buf[64];
	rargs = (struct pthread_args *)arg;
	printf("in thread:%s,autoval=%d\n",rargs->s,*rargs->autovar);
	printf("flag = %d\n",flag);
	if(read(rargs->fd,buf,64) < 0){
		err_sys("read error");
	}
	printf("the content read:%s\n",buf);
	print_thread_id("new thread:");
	return (void *)0;
}

int main(){
	pthread_t pthid;
	int var,fd;
	struct pthread_args args;

	var = 3;
	flag = 2;
	if((fd = open("makefile",O_RDONLY)) < 0){
		err_sys("open error");
	}

	args.s = "hello world";
	args.autovar = &var;
	args.fd = fd;
	if(pthread_create(&pthid,NULL,thr_fn,&args) != 0){
		err_sys("can't create thread");
	}
	print_thread_id("main thread:");
	sleep(1);
	exit(0);
}
