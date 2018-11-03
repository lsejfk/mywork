#include "hstring.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUMBER 1
#define OPERATOR 2

typedef int ComputeType;
ComputeType computeValue(const char *str);
void inffixtosuffix(char *inffix,char *suffix);
void suffixtoinffix(char *suffix,char *inffix);

int main(){
	char arr[128];
	char *suffix = "32 -2 4 * + 5 6 * 9 + 2 * +";
	//inffixtosuffix(inffix,suffix);
//	printf("inffix:%s\nsuffix:%s\n",inffix,suffix);
	suffixtoinffix(suffix,arr);
	printf("suffix:%s\ninffix:%s\n",suffix,arr);
/*
	char str[100];

	if(fgets(str,100,stdin) == NULL){
		fprintf(stderr,"read input error\n");
		exit(-1);
	}
	printf("the result=%d\n",computeValue(str));
	*/
	return 0;
}


int isOperator(char ch){
	static char operator[] = {'+','-','*','/','(',')','^'};
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
int optPiror(char opteror){
	switch(opteror){
		case '+':
		case '-':return 1;break;
		case '*':
		case '/':return 2;break;
		case '^':return 3;break;
		case '(':return 4;break;
	}
}
void inorout(char buf[],Stack S,char ch){
	int len;
	char opt[32];
	int k = 0;
	len = strlen(buf);
	if(ch == ')'){
		while(!arr_isEmpty(S) && arr_top(S) != '('){
			opt[k++] = arr_topAndPop(S);
		}
		opt[k++] = ' ';
		opt[k] = '\0';
		if(!arr_isEmpty(S) && arr_top(S) == '('){
			arr_pop(S);
		}else{
			fprintf(stderr,"invalid inffix\n");
			exit(-1);
		}
	}else{
		while(!arr_isEmpty(S) && optPiror(arr_top(S)) >= optPiror(ch)){
				if(arr_top(S) == '('){
					break;
				}
				opt[k++] = arr_topAndPop(S);
		}
		opt[k++] = ' ';
		opt[k] = '\0';
		arr_push(ch,S);
	}
	strcat(buf,opt);
}

void inffixtosuffix(char *inffix,char *suffix){
	Stack S;
	int i,j,k,option;
	char *buf,*p;
	char s[32],tmp[64];
	if(system("./settype.sh char") < 0){
		fprintf(stderr,"system() error");
		exit(-1);
	}
	S = arr_createStack(strlen(inffix));
	buf = (char *)calloc(2 * strlen(inffix),sizeof(char));
	if(buf == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	p = inffix;
	while((option = getOption(inffix,s))){
		switch(option){
			case NUMBER:
				sprintf(tmp,"%s ",s);
				strcat(buf,tmp);
				break;
			case OPERATOR:
				inorout(buf,S,s[0]);
				break;
			default:
				fprintf(stderr,"invalid option\n");
				exit(-1);
				break;
		}//switch
	}//while
	k = 0;
	while(!arr_isEmpty(S)){
		tmp[k++] = arr_topAndPop(S);
	}
	tmp[k++] = ' ';
	tmp[k] = '\0';
	strcat(buf,tmp);
	strcpy(suffix,buf);
	arr_disposeStack(S);

}

int getlowestprior(char *str){
	int i,len,option,tmp,prior;
	char s[64];
	len = strlen(str);
	prior = 5;
	while((option = getOption(str,s))){
		if(option == OPERATOR){
			tmp = optPiror(s[0]);
			prior = prior < tmp ? prior : tmp; 
		}
	}
	return prior;
}

//transfer from suffix to inffix
void suffixtoinffix(char *suffix,char *inffix){
	Stack S;
	ArrStackType str,left,right,res;
	int i,j,k,option,prior;
	char s[64];
	S = arr_createStack(strlen(suffix));
	while((option = getOption(suffix,s))){
		switch(option){
			case NUMBER:
				str = hstrassign(s);
				printf("%s\n",str->str);
				arr_push(str,S);
				break;
			case OPERATOR:
				str = hstrassign(s);
				hstraddleft(str," ");
				hstraddright(str," ");
				right = arr_topAndPop(S);
				prior = getlowestprior(right->str);
				if(prior < optPiror(s[0])){
					hstraddleft(right,"(");
					hstraddright(right,")");
				}
				left = arr_topAndPop(S);
				prior = getlowestprior(right->str);
				if(prior < optPiror(s[0])){
					hstraddleft(left,"(");
					hstraddright(left,")");
				}
				res = hstrconcat(hstrconcat(left,str),right);
				arr_push(res,S);
				hstrdestroy(str);
				hstrdestroy(left);
				hstrdestroy(right);
				break;
			default:
				fprintf(stderr,"invalid option\n");
				exit(-1);
		}//switch
	}//while
	str = arr_topAndPop(S);
	strcpy(inffix,str->str);
	hstrdestroy(str);
	arr_disposeStack(S);
}
