#include "MultLinkStack.h"

//initialize the stack
void initMultLinkStack(MultLinkStack *st,VARTYPE size){
	MultLinkNode *p;
	p = (MultLinkNode *)malloc(sizeof(MultLinkNode));		//create the head node
	if(p == NULL){
		fprintf(stderr,"error:initMultLinkStack:malloc p failed\n");
		return;
	}
	st->num = 0;
	st->first = st->last = p;
	p->next = NULL;
	st->size = size;
}

//buynode
static MultLinkNode *buyMLNode(MultLinkStack *st,const void *elem){
	MultLinkNode *p;
	unsigned char *e;
	if((p = (MultLinkNode *)malloc(sizeof(MultLinkNode))) == NULL){		//create node
		fprintf(stderr,"error:push:malloc p failed\n");
		return NULL;
	}
	p->next = NULL;
	if((p->data = (unsigned char *)malloc(st->size)) == NULL){		//allocate a space for storing the element
		fprintf(stderr,"error:push:malloc p->data failed\n");
		return NULL;
	}
	e = (unsigned char *)elem;						//transfer the type into unsigned char
	*(p->data) = *e;		//store the element
	return p;
}

//push
void push(MultLinkStack *st,const void *elem){
	MultLinkNode *p;
	p = buyMLNode(st,elem);			//create a node
	p->next = st->first->next;
	st->first->next = p;
	if(st->num == 0){			//the stack is empty
		st->last = p;
	}
	st->num++;
}


//pop
void *pop(MultLinkStack *st){
	MultLinkNode *p;
	if(st->num == 0){
		return NULL;
	}
	p = st->first->next;
	st->first->next = p->next;
	if(st->num == 1){
		st->last = st->first;
	}
	st->num--;
	return (void *)(p->data);
}


//get top element
void *getTop(MultLinkStack *st){
	MultLinkNode *p;
	if(st->num == 0){
		return NULL;
	}
	p = st->first->next;
	return (void *)(p->data);
}

//check if the stack is empty
int isStackEmpty(MultLinkStack *st){
	return (st->num == 0);
}
