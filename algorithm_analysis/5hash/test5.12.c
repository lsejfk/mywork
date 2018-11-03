#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096
#define MAX_NUM_LINES 1000 
#define START 0
int first = 0;
int hash(int key,int tabsize){
	int diff;
	diff = key - first;
	return (START + diff) % tabsize;
}
char * copyword(char *key){
	char *res;
	res = (char *)calloc(strlen(key) + 1,sizeof(char));
	if(res == NULL){
		fprintf(stderr,"calloc error\n");
		exit(-1);
	}
	strncpy(res,key,strlen(key));
	return res;
}

int nextprime(int the){
	int k,res;
	if(the < 3){
		return 2;
	}else if(the < 5){
		return 3;
	}else if(the < 7){
		return 5;
	}else{
		k = the / 6;
		if((res = 6 * k + 1) >= the){
			return res;
		}else if((res = 6 * k + 5) >= the){
			return res;
		}
	}
	return the;
}
int main(){
	FILE *fp;
	char line[MAXLINE+1];
	char **hashtab;
	int tabsize,seq;
	tabsize = nextprime(MAX_NUM_LINES);
	hashtab = (char **)calloc(tabsize,sizeof(char *));
	if(hashtab == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}

	if((fp = fopen("basic","r")) == NULL){
		fprintf(stderr,"fopen error\n");
		exit(-1);
	}
	if(fgets(line,MAXLINE,fp) != NULL){
		first = atoi(line);
		hashtab[hash(first,tabsize)] = copyword(line);
	}
	while(fgets(line,MAXLINE,fp) != NULL){
		seq = atoi(line);
		hashtab[hash(seq,tabsize)] = copyword(line);
	}

	printf("11:%s\n",hashtab[hash(11,tabsize)]);
	return 0;
}


