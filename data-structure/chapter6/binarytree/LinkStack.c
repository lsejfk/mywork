#include "LinkStack.h"

//initialization
void initLinkStack(LinkStack *s){
	LinkNode *p;
	p = (LinkNode *)malloc(sizeof(LinkNode));	//create the head node
	p->next = NULL;
	s->size = 0;
	s->first = s->last = p;
}

//push
void push(LinkStack *s,LinkStackElemType v){
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	p->e = v;
	p->next = s->first->next;
	s->first->next = p;
	if(s->size == 0){	//this stack is empty
		s->last = p;
	}
	s->size++;
}

//pop
void pop(LinkStack *s,LinkStackElemType *v){
	LinkNode *p;
	if(s->size == 0){
		printf("error:the stack is empty!\n");
		exit(1000);
	}else{
		p = s->first->next;
		s->first->next = p->next;
		*v = p->e;
		free(p);
		if(s->size == 1){
			s->last = s->first;	//change the tail pointer
		}
		s->size--;
	}
}

//get the top element of the stack
void getTop(LinkStack *s,LinkStackElemType *v){
	LinkNode *p;
	if(s->size == 0){
		printf("getTop error:the stack is empty!\n");
		exit(1001);
	}else{
		p = s->first->next;
		*v = p->e;
	}
}

//check if the stack is empty
int isEmpty(LinkStack *s){
	return (s->size == 0) ? 1 : 0;
}

