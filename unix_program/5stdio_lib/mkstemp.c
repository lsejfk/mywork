#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

void make_tmp(char template[]);

int main(){
	char good_template[] = "good_XXXXXXX";
	char *bad_template = "bad_XXXXXX";

	printf("trying to make the first tempfile\n");
	make_tmp(good_template);
	printf("trying to make the second tempfile\n");
	make_tmp(bad_template);
	return 0;

}

void make_tmp(char template[]){
	int fd;
	struct stat buf;
	if((fd = mkstemp(template)) < 0){
		err_sys("mkstemp error");
	}
	printf("file name:%s\n",template);
	close(fd);
	printf("%s closed\n",template);
	sleep(5);
	if(stat(template,&buf) < 0){
		if(errno == ENOENT){
			printf("file don't exist\n");
			return;
		}else{
			err_sys("stat error");
		}
	}else{
		printf("file exist\n");
		unlink(template);
	}
}
