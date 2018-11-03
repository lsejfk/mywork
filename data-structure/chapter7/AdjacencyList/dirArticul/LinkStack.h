#ifndef LINKSTACK_H
#define LINKSTACK_H
#include<stdio.h>
#include<stdlib.h>
#include "AdjacencyList.h"

#define LinkStackElemType ArcNode*


typedef struct LinkNode{
	LinkStackElemType e;	//the element of the node
	struct LinkNode *next;
}LinkNode;

typedef struct LinkStack{
	int size;		//the number of elements in the stack
	LinkNode *first;	//first pointer to the head
	LinkNode *last;		//last pointer to the tail
}LinkStack;


void initLinkStack(LinkStack *s);	//initialization
void push(LinkStack *s,LinkStackElemType v);	//push
void pop(LinkStack *s,LinkStackElemType *v);	//pop
void getTop(LinkStack *s,LinkStackElemType *v);	//get the top element of the stack
int isEmpty(LinkStack *s);			//check if the stack is empty

#endif
