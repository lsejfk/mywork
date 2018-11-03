#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <pwd.h>

struct passwd *getpwname(char *name){
	struct passwd *ptr;
	setpwent();	//self-defence
	while((ptr = getpwent())){
		if(strcmp(name,ptr->pw_name) == 0){	//find the entry
			break;
		}
	}
	endpwent();
	return ptr;
}

int main(){
	struct passwd *ptr;
	if((ptr = getpwname("michael")) == NULL){
		err_ret("michael don't exist");
	}
	printf("user name:%s\nencrypted password:%s\nnumerical user id:%d\ngroup id:%d\nconment:%s\n",
		ptr->pw_name,ptr->pw_passwd,ptr->pw_uid,ptr->pw_gid,ptr->pw_gecos);
	return 0;
}
