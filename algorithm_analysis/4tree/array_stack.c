#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr_isEmpty(Stack S){
	return S->topofstack == EmptyTag;
}

int arr_isFull(Stack S){
	return S->topofstack == S->capacity - 1;
}

Stack arr_createStack(int maxElems){
	Stack S;
	S = (struct StackRecord *)malloc(sizeof(struct StackRecord));
	if(S == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	S->capacity = maxElems;
	S->topofstack = EmptyTag;
	S->arr = (ArrStackType *)calloc(maxElems,sizeof(ArrStackType));
	if(S->arr == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}

	return S;
}

void arr_disposeStack(Stack S){
	if(S != NULL){
		free(S->arr);
		free(S);
	}
}

void arr_makeEmpty(Stack S){
	if(S != NULL){
		S->topofstack = EmptyTag;
	}
}

void arr_push(ArrStackType x,Stack S){
	if(!arr_isFull(S)){
		S->arr[++S->topofstack] = x;
	}else{
		fprintf(stderr,"array stack out of space\n");
		exit(-1);
	}
}

ArrStackType arr_top(Stack S){
	if(arr_isEmpty(S)){
		fprintf(stderr,"empty Stack\n");
		return 0;
	}
	return S->arr[S->topofstack];
}

void arr_pop(Stack S){
	if(arr_isEmpty(S)){
		fprintf(stderr,"Empty Stack\n");
	}else{
		S->topofstack--;
	}
}

ArrStackType arr_topAndPop(Stack S){
	if(arr_isEmpty(S)){
		fprintf(stderr,"Empty Stack\n");
		return 0;
	}
	return S->arr[S->topofstack--];
}

//change the element type
void arr_changetype(char *type){
	char comm[128];
	strcpy(comm,"/home/michael/local/src/settype.sh ");
	strcat(comm,type);
	if(system(comm) < 0){
		fprintf(stderr,"system() error");
		exit(-1);
	}
}
