#include "avltree.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

static AvlTree singleRolateLeft(AvlTree T){
	AvlPosition p;
	p = T->left;

	T->left = p->right;
	p->right = T;
	T->height = max(avl_height(T->left),avl_height(T->right)) + 1;
	p->height = max(avl_height(T),avl_height(p->left)) + 1;
	return p;
}	

static AvlTree singleRolateRight(AvlTree T){
	AvlPosition p;
	p = T->right;

	T->right = p->left;
	p->left = T;
	T->height = max(avl_height(T->left),avl_height(T->right)) + 1;
	p->height = max(avl_height(T),avl_height(p->right)) + 1;
	return p;
}

static AvlTree doubleRolateLeft(AvlTree T){
	T->left = singleRolateRight(T->left);
	return singleRolateLeft(T);
}

static AvlTree doubleRolateRight(AvlTree T){
	T->right = singleRolateLeft(T->right);
	return singleRolateRight(T);
}
//1-left,left 2-left-right 3-right-right 4-right-right
static int gettype(AvlTree T,AvlElemType x){
	if(T == NULL){
		return 0;
	}
	if(x < T->elem){
		if(x < T->left->elem){
			return 1;
		}else if(x > T->left->elem){
			return 2;
		}else{
			return 0;
		}
	}else if(x > T->elem){
		if(x > T->right->elem){
			return 3;
		}else if(x < T->right->elem){
			return 4;
		}else{
			return 0;
		}
	}
}

static AvlTree doRolate(AvlPosition p,int type){
	switch(type){
		case 1:
			return singleRolateLeft(p);
			break;
		case 2:
			return doubleRolateLeft(p);
			break;
		case 3:
			return singleRolateRight(p);
			break;
		case 4:
			return doubleRolateRight(p);
			break;
		default:
			return NULL;
	}//switch
}

AvlTree avlinsert(AvlElemType x,AvlTree T){
	Stack S;
	int type;
	AvlPosition p,q,n;
	S = arr_createStack(100);
	q = T;
	n = (AvlPosition)malloc(sizeof(struct AvlNode));
	if(n == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	n->elem = x;
	n->left = n->right = NULL;
	n->height = 0;
	p = T;
	if(p == NULL){
		return n;
	}
	while(p){
		arr_push(p,S);
		if(x < p->elem){
			p = p->left;
		}else if(x > p->elem){
			p = p->right;
		}else{
			arr_disposeStack(S);
			return T;
		}
	}
	q = arr_top(S);
	if(x < q->elem){
		q->left = n;
	}else if(x > q->elem){
		q->right = n;
	}

	while(!arr_isEmpty(S)){
		p = arr_topAndPop(S);
		p->height = max(avl_height(p->left),avl_height(p->right)) + 1;
		if(abs(avl_height(p->left)-avl_height(p->right)) == 2){
			type = gettype(p,x);		//get the inserting type
			q = doRolate(p,type);
			if(!arr_isEmpty(S)){
				n = arr_top(S);
				if(x < n->elem){
					n->left = q;
				}else if(x > n->elem){
					n->right = q;
				}
			}else{
				return q;
			}
		}//if abs
	}//while
	arr_disposeStack(S);
	return T;
}

static void printTree(AvlTree T){
	if(T == NULL){
		return;
	}
	printTree(T->left);
	printf("%d,",T->elem);
	printTree(T->right);
}

int main(){
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int i;
	AvlTree T;
	T = NULL;
	for(i=0;i<16;i++){
		T = avlinsert(arr[i],T);
	}
	printTree(T);
}
