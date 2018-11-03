#include "Stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//initialize
void initStack(Stack *st){
	st->num = 0;
	st->top = 0;
	st->capacity = MAX_STACK_SIZE; 
	st->stack = (StackElemType *)malloc(sizeof(StackElemType) * MAX_STACK_SIZE);
	assert(st->stack != NULL);
}

//push
void stack_push(Stack *st,StackElemType e){
	if(st->top >= st->capacity){		//full stack
		st->stack = (StackElemType *)realloc(st->stack,st->capacity + STACK_INCREMENT);
		assert(st->stack != NULL);
		st->capacity += STACK_INCREMENT;
	}
	++st->num;
	st->stack[st->top++] = e;
}

//pop
void stack_pop(Stack *st,StackElemType *v){
	if(st->top == 0){			//empty stack
		return;
	}
	st->num--;
	*v = st->stack[--st->top];
}

//get top element
int stack_getTop(Stack *st,StackElemType *v){
	if(st->top == 0){
		return 0;
	}
	*v = st->stack[st->top - 1];
}

//check if the stack is empty
int stack_isEmpty(Stack *st){
	return (st->top == 0);
}

//clean the stack
void stack_clean(Stack *st){
	st->top = 0;
	st->num = 0;
}

//destroy the stack
void stack_destory(Stack *st){
	stack_clean(st);
	st->capacity = 0;
	free(st->stack);
}
