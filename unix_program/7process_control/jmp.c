#include "apue.h"
#include "myerr.h"
#include <setjmp.h>
#include <stdlib.h>
#include <ctype.h>

#define ADD_TOKEN 5

jmp_buf jmpval;
static int vector = 0;		//record the location of line
void do_line(char *line);
int get_cmd(char *line);
void add_token(char *line);
int get_token(char *line);

int flag = 0;
int nflag = 0;

int main(int argc,char *argv[]){
	char line[1000];
	nflag++;
	if(setjmp(jmpval) != 0){
		printf("error\n");
	}
	flag++;
	printf("flag = %d,nflag = %d\n",flag,nflag);
	printf("line : %s\n",line);
	while(fgets(line,1000,stdin) != NULL){
		printf("do_line action\n");
		do_line(line);
	}
}


void do_line(char *line){
	int cmd;
	vector = 0;
	printf("get_cmd action\n");
	while((cmd = get_cmd(line)) != 0){
		switch(cmd){
			case ADD_TOKEN:
				printf("add_token action\n");
				 add_token(line);
				break;
			default:
				printf("default\n");
				break;
		}//switch
		printf("get_cmd action\n");
	}//while
}

int get_cmd(char *line){
	char str[1000];
	int i;
	i = 0;
	while(line[vector] && isspace(line[vector])){
		vector++;
	}
	while(line[vector] != '\0' && !isspace(line[vector])){
		str[i++] = line[vector++];
	}
	str[i] = '\0';
	if(i == 0){	//line get to '\0'
		return 0;
	}
	return atoi(str);
}

void add_token(char *line){
	static int mytoken = 0;
	int token;
	printf("get_token action\n");
	while((token = get_token(line))){
		if(token < 0){	//invalid
			printf("long jmp for add_token\n");
			longjmp(jmpval,1);	//return to main function
		}//if token
		mytoken += token;
	}//while
}

int get_token(char *line){
	char str[1000];
	int i,tmp;
	i = 0;
	while(line[vector] && isspace(line[vector])){
		vector++;
	}
	while(line[vector] && !isspace(line[vector])){
		str[i++] = line[vector++];
	}
	str[i] = '\0';
	if(i == 0){
		return 0;
	}
	if((tmp = atoi(str)) == 0){	//token must be digit
		printf("longjmp from get_token\n");
		longjmp(jmpval,2);
	}
	return tmp;

}


