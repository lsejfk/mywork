#include "array_stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char startchar[] = {'b','(','[','{'};
static char endchar[] 	 = {'e',')',']','}'};

#define Numarr (sizeof(startchar) / sizeof(startchar[0]))
void check_str(char *str);

int main(){
	char *str = "begin asdfljasd asdfljassdf  (slsjf sldfjsdl]lsdjfla asdlfj)lf asd end lasdfjald{asldf as end";
	printf("%s\n",str);
	check_str(str);
	return 0;
}


int isStartChar(char ch){
	int i;
	for(i=0;i<Numarr;i++){
		if(ch == startchar[i]){
			return 1;
		}
	}
	return 0;
}

int isEndChar(char ch){
	int i;
	for(i=0;i<Numarr;i++){
		if(ch == endchar[i]){
			return 1;
		}
	}
	return 0;
}

char pattern(char ch){
	int i;
	for(i=0;i<Numarr;i++){
		if(ch == endchar[i]){
			return startchar[i];
		}else if(ch == startchar[i]){
			return endchar[i];
		}
	}
	return 0;
}

void check_str(char *str){
	int len;
	int i,k;
	char save[64],ch;
	Stack S;
	S = arr_createStack(len);

	len = strlen(str);
	for(i=0;i<len;i++){
		if(str[i] == 'b' || str[i] == 'e'){
			k = 0;
			while(isalpha(str[i])){
				save[k++] = str[i++];
			}
			save[k] = '\0';
			--i;
			if(strcmp(save,"begin") == 0){
				arr_push('b',S);
			}else if(strcmp(save,"end") == 0){
				ch = arr_top(S);
				if(ch == 0 || ch != 'b'){
					fprintf(stderr,"lose start flag of begin at %d\n",i);
				}else{
					arr_pop(S);
				}
			}
		}else if(isStartChar(str[i])){
			arr_push(str[i],S);
		}else if(isEndChar(str[i])){
			ch = arr_top(S);
			if(ch == 0){
				fprintf(stderr,"lose the start char of %c at %d\n",pattern(str[i]),i);
			}else if(ch != pattern(str[i])){
				fprintf(stderr,"lose the start char of %c at %d\n",pattern(str[i]),i);
			}else{
				arr_pop(S);
			}
		}
	}//for
	while(!arr_isEmpty(S)){
		fprintf(stderr,"lose the end char of %c\n",pattern(arr_top(S)));
		arr_pop(S);
	}
	arr_disposeStack(S);
}
