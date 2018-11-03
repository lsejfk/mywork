#ifndef STACK_H
#define STACK_H
#define MAX_STACK_SIZE 20
#define STACK_INCREMENT 10
typedef int StackElemType;

typedef struct Stack{
	int num;		//the number of elements
	int top;		//the top element pointer
	int capacity;		//the stack's capacity
	StackElemType *stack;	//element array,initialized by initStack()
}Stack;
void initStack(Stack *st);
void stack_push(Stack *st,StackElemType e);
void stack_pop(Stack *st,StackElemType *v);
int stack_getTop(Stack *st,StackElemType *v);
int stack_isEmpty(Stack *st);
void stack_clean(Stack *st);
void stack_destory(Stack *st);

#endif
