#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int gloval = 3;

static void test(){
	int hello;
	hello = 6;
	printf("function in test:hello=%d\n");
}
static int test_func(){
	int test = 5;
	pid_t pid;
	printf("function in test_func:gloval=%d,test=%d\n",gloval,test);
	if((pid = vfork()) < 0){
		err_sys("vfork error");
	}else if(pid == 0){
		printf("at the vfork child:gloval=%d,test=%d\n",gloval,test);
		printf("gloval add one\n");
		gloval++;
	}

	printf("function in test_func after child process:gloval=%d,test=%d\n",gloval,test);
	return test;
}
int main(){
	int mainval = 4;
	pid_t pid;
	printf("function in main:gloval=%d,mainval=%d\n",gloval,mainval);
	printf("function in main:test_func return value=%d\n",test_func());
	return 0;
}
