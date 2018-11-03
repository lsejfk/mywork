#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFSIZE 4096

int main(int argc,char *argv[]){
	int i;
	int num,len;
	int total;
	FILE *fp;
	char buf[BUFSIZE];
	char digit[20];
	if(argc != 2){
		fprintf(stderr,"usage:a.out <number>\n");
		return -1;
	}

	if((fp = fopen("data","a+")) == NULL){
		fprintf(stderr,"fopen error for data\n");
		return -1;
	}

	for(i=atoi(argv[1]);i>0;i--){
		num = rand();
		sprintf(digit,"%d ",num);
		len = strlen(digit);
		if((len + total) >= BUFSIZE){		//fflush buf into disk
			if(fwrite(buf,sizeof(char),total,fp) != total){
				fprintf(stderr,"fwrite error\n");
				return -1;
			}
			fflush(fp);
			total = 0;
			strcat(buf,digit);
			total += len;
		}else{
			strcat(buf,digit);
			total += len;
		}
	}
	
}
