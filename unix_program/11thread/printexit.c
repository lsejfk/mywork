#include "apue.h"
#include "myerr.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
struct pthreadreturn_tag{
	int exitcode;
	char info[64];
};

void *pfun1(void *arg){
	printf("thread 1 returns:\n");
	return (void *)1;
}

void *pfun2(void *arg){
	struct pthreadreturn_tag *p;
	printf("thread 2 returns:\n");
	/*
	err = pthread_join(*((pthread_t *)arg),&res);
	if(err != 0){
		err_sys("pthread_join error");
	}
	printf("in thread 2 ,fetch thread 1 exit status:%ld\n",(long)res);
	*/
	p = (struct pthreadreturn_tag *)malloc(sizeof(struct pthreadreturn_tag));
	if(p == NULL){
		err_sys("malloc failed");
	}
	p->exitcode = 2;
	strncpy(p->info,"this is test of returning a structure\n",64);
	pthread_exit((void *)p);
}

int main(){
	pthread_t tid1,tid2;
	void *exitres;
	int err;
	struct pthreadreturn_tag *p;

	err = pthread_create(&tid1,NULL,pfun1,NULL);
	if(err != 0){
		err_sys("pthread_create error");
	}
	err = pthread_create(&tid2,NULL,pfun2,&tid1);
	if(err != 0){
		err_sys("can't create pthread2");
	}

	err = pthread_join(tid2,&exitres);
	if(err != 0){
		err_sys("fetch thread 1 exit status error");
	}
	p = (struct pthreadreturn_tag *)exitres;
	printf("thread 2 exit status:%ld\n%s",(long)p->exitcode,p->info);

	err = pthread_join(tid1,&exitres);
	if(err != 0){
		err_sys("fetch thread 2 exit status error");
	}
	printf("thread 1 exit status:%ld\n",(long)exitres);
	printf("seconde:thread 2 exit status:%ld\n%s",(long)p->exitcode,p->info);

	return 0;
}
