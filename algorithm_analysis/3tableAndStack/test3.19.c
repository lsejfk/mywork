#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define NUMBER 1
#define OPERATOR 2

typedef int ComputeType;
ComputeType computeValue(const char *str);

int main(){
	char str[100];

	if(fgets(str,100,stdin) == NULL){
		fprintf(stderr,"read input error\n");
		exit(-1);
	}
	printf("the result=%d\n",computeValue(str));
	return 0;
}


int isOperator(char ch){
	static char operator[] = {'+','-','*','/'};
	int num = sizeof(operator) / sizeof(operator[0]);
	int i;
	for(i=0;i<num;i++){
		if(ch == operator[i]){
			return 1;
		}
	}
	return 0;
}
int getOption(const char *str,char s[]){
	static int i = 0;
	int j;
	int len = strlen(str);
	while(i < len && isspace(str[i])){
		i++;
	}
	if(i >= len){
		return 0;
	}	
	j = i;
	if(isdigit(str[j])){
		j = 0;
		while(i < len && isdigit(str[i])){
			s[j++] = str[i++];
		}
		s[j] = '\0';
		return NUMBER;
	}else if(isOperator(str[j])){
		j = 0;
		if(str[i] == '-'){
			if(isdigit(str[i+1])){
				s[j++] = str[i++];
				while(i < len && isdigit(str[i])){
					s[j++] = str[i++];
				}
				s[j] = '\0';
				return NUMBER;
				
			}
		}
		s[j++] = str[i++];
		s[j] = '\0';
		return OPERATOR;
	}else if(isalpha(str[j])){
		j = 0;
		while(i < len && isalpha(str[i])){
			s[j++] = s[i++];
		}
		s[j] = '\0';
		return OPERATOR;
	}else{
		return 0;
	}
}

void doOption(char op,Stack S){
	ComputeType left,right,res;
	switch(op){
		case '+':
			arr_push((arr_topAndPop(S) + arr_topAndPop(S)),S);
			break;
		case '-':
			right = arr_topAndPop(S);
			left = arr_topAndPop(S);
			res = left - right;
			arr_push(res,S);
			break;
		case '*':
			arr_push((arr_topAndPop(S) * arr_topAndPop(S)),S);
			break;
		case '/':
			right = arr_topAndPop(S);
			left = arr_topAndPop(S);
			res = left / right;
			arr_push(res,S);
			break;
		default:
			fprintf(stderr,"invalid operator\n");
			exit(-1);
	}
}

ComputeType computeValue(const char *str){
	int len,i,num,option;
	char s[32];
	Stack S;
	ComputeType res;

	S = arr_createStack(strlen(str));

	while((option = getOption(str,s))){
		switch(option){
			case NUMBER:
				num = atoi(s);
				arr_push(num,S);
				break;
			case OPERATOR:
				doOption(s[0],S);
				break;
			default:
				fprintf(stderr,"invalid option\n");
				return 0;
				break;
		}//switch
	}//while
	res = arr_top(S);
	arr_disposeStack(S);
	return res;
}
