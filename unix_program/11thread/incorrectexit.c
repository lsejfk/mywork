#include "apue.h"
#include "myerr.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct extest{
	int a,b,c,d;
};

void printfoo(const char *s,const struct extest *fp){
	printf("%s",s);
	printf(" structure at 0x%lx\n",(unsigned long)fp);
	printf(" foo.a=%d\n",fp->a);
	printf(" foo.b=%d\n",fp->b);
	printf(" foo.c=%d\n",fp->c);
	printf(" foo.d=%d\n",fp->d);
}

void *pfun1(void *arg){
	struct extest foo = {1,2,3,4};
	printfoo("thread 1:\n",&foo);
	pthread_exit((void *)&foo);
}
void *pfun2(void *arg){
	printf("thread 2:ID is %lu\n",(unsigned long)pthread_self());
	pthread_exit((void *)0);
}
int main(){
	pthread_t tid1,tid2;
	struct extest *fp;
	int err;

	err = pthread_create(&tid1,NULL,pfun1,NULL);
	if(err != 0){
		err_sys("can't create thread 1");
	}
	err = pthread_join(tid1,(void *)&fp);
	if(err != 0){
		err_sys("can't join with thread 1");
	}
	//sleep(1);
	printf("parent start second thread\n");

	err = pthread_create(&tid2,NULL,pfun2,NULL);
	if(err != 0){
		err_sys("can't create thread 2");
	}
	err = pthread_join(tid2,(void *)&fp);
	if(err != 0){
		err_sys("can't join with thread 1");
	}
	//sleep(1);
	printfoo("parent:\n",fp);
	
	exit(0);
}
