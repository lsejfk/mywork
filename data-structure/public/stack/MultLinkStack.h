#ifndef MULTLINKSTACK_H
#define MULTLINKSTACK_H
#include<stdio.h>
#include<stdlib.h>
typedef long unsigned int VARTYPE;
typedef struct MultLinkNode{
	unsigned char *data;			//the element value
	struct MultLinkNode *next;
}MultLinkNode;

typedef struct MultLinkStack{
	int num;
	MultLinkNode *first;		//the head node
	MultLinkNode *last;		//the last node
	VARTYPE size;			//the size int this type of the variable 
}MultLinkStack;
void initMultLinkStack(MultLinkStack *st,VARTYPE size);
void push(MultLinkStack *st,const void *elem);
void *pop(MultLinkStack *st);
void *getTop(MultLinkStack *st);
int isStackEmpty(MultLinkStack *st);
#endif
