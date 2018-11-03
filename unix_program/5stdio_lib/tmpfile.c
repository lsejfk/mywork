#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 4096

int main(){
	char line[MAX_LINE],filename[L_tmpnam];
	FILE *fp;
	printf("first tmpname:%s\n",tmpnam(NULL));
	printf("waiting for 5 seconds...\n");
	sleep(5);
	tmpnam(filename);
	printf("second tmpname:%s\n",filename);
	if((fp = tmpfile()) == NULL){
		err_sys("tmpfile error\n");
	}
	if(fputs("this is one line",fp) == EOF){		//Write one line to the tmpfile
		err_sys("fputs error");
	}
	rewind(fp);		//return to the beginning
	if(fgets(line,sizeof(line),fp) == NULL){
		err_sys("fgets error");
	}
	printf("line:%s\n",line);
	return 0;	
}
