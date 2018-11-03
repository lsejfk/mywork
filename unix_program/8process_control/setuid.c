#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>

int main(){
	uid_t uid,eid;
	uid = getuid();
	eid = geteuid();
	printf("before set\nreal user id=%d,effective user id=%d\n",uid,eid);
	printf("real group id=%d,effective group id=%d\n",getgid(),getegid());
	printf("set-user-id=%d\n",getresuid());
	if(setuid(1000) < 0){
		err_sys("setuid error");
	}
	printf("after set\nreal user id=%d,effective user id=%d,set-user-id=%d\n",getuid(),geteuid(),getresuid());
	return 0;
}
