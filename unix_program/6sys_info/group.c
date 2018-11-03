#include "apue.h"
#include "myerr.h"
#include <grp.h>

int main(){
	struct group *ptr;
	char **p;
	setgrent();	//self-defence
	while((ptr = getgrent())){
		printf("grname:%s passwd:%s gid:%d\n membes:\n",ptr->gr_name,ptr->gr_passwd,ptr->gr_gid);
		p = ptr->gr_mem;
		while(p && *p){
			printf("%s\n",*p++);
		}
		
	}
	return 0;
}
