#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#define EmptyTag -1
typedef int ExTreeElemType;
struct ExTreeNode{
	ExTreeElemType elem;
	struct ExTreeNode *left;
	struct ExTreeNode *right;
};
typedef struct ExTreeNode *ExTree;
typedef ExTree ExPosition;

typedef ExPosition ArrStackType;

struct StackRecord{
	int capacity;
	int topofstack;
	ArrStackType *arr;
};

typedef struct StackRecord *Stack;

int arr_isEmpty(Stack S);
int arr_isFull(Stack S);
Stack arr_createStack(int maxElems);
void arr_disposeStack(Stack S);
void arr_makeEmpty(Stack S);
void arr_push(ArrStackType x,Stack S);
ArrStackType arr_top(Stack S);
void arr_pop(Stack S);
ArrStackType arr_topAndPop(Stack S);
void arr_changetype(char *type);

#endif
