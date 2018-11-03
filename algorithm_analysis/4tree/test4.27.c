#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>

ExTree ex_insert(ExTree T,ExTreeElemType x){
	if(T == NULL){
		T = (ExPosition)malloc(sizeof(struct ExTreeNode));
		if(T == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		T->elem = x;
		T->left = T->right = NULL;
	}else{
		if(x < T->elem){
			T->left = ex_insert(T->left,x);
		}else if(x > T->elem){
			T->right = ex_insert(T->right,x);
		}
	}
	return T;
}

static ExPosition rolate(ExPosition grandf,ExPosition father,ExPosition me){
	ExPosition p,q;
	
	if(father->elem < grandf->elem){
		if(me->elem < father->elem){
			p = me->right;
			me->right = father;
			father->left = p;
			p = father->right;
			father->right = grandf;
			grandf->left = p;
		}else if(me->elem > father->elem){
			p = me->left;
			q = me->right;
			me->left = father;
			me->right = grandf;
			father->right = p;
			grandf->left = q;
		}
	}else if(father->elem > grandf->elem){
		if(me->elem < father->elem){
			p = me->left;
			q = me->right;
			me->left = grandf;
			me->right = father;
			grandf->right = p;
			father->left = q;
		}else if(me->elem > father->elem){
			p = me->left;
			me->left = father;
			father->right = p;
			p = father->left;
			father->left = grandf;
			grandf->right = p;
		}
	}
	return me;
}

static ExTree rolate_adjust(Stack S,ExPosition p){
	int level;
	ExPosition q,s,r;
	level = 0;
	r = NULL;
	while(!arr_isEmpty(S)){
		if(level == 0){
			q = arr_topAndPop(S);
			level++;
			if(r){
				if(p->elem < q->elem){
					q->left = r;
				}else if(p->elem > q->elem){
					q->right = r;
				}
				r = NULL;
			}
		}else if(level == 1){
			s = arr_topAndPop(S);
			r = rolate(s,q,p);
			level = 0;
		}
	}
	if(level == 0){
		if(r){
			return r;
		}else{
			return p;
		}
	}else if(level == 1){
		if(p->elem < q->elem){
			q->left = p->right;
			p->right = q;
			return p;
		}else if(p->elem > q->elem){
			q->right = p->left;
			p->left = q;
			return p;
		}
	}
	return p;
}

ExTree ex_find(ExTree T,ExTreeElemType x){
	Stack S;
	ExPosition p;
	S = arr_createStack(100);
	if(T == NULL){
		return NULL;
	}
	p = T;
	//find the element and store the find-path
	while(p && p->elem != x){
		arr_push(p,S);	
		if(x < p->elem){
			p = p->left;
		}else if(x > p->elem){
			p = p->right;
		}
	}
	if(p == NULL){
		return NULL;
	}
	return rolate_adjust(S,p);
}

static void printTree(ExTree T){
	if(T){
		printf("%d,",T->elem);
		printTree(T->left);
		printTree(T->right);
	}
}


static int numofnodes(ExTree T){
	int nleft,nright;
	if(T == NULL){
		return 0;
	}else{
		nleft = numofnodes(T->left);
		nright = numofnodes(T->right);
		return nleft + nright + 1;
	}
}

static int numofleaves(ExTree T){
	static int count = 0;
	if(T == NULL){
		return 0;
	}else if(T->left == NULL && T->right == NULL){
		count++;
	}else{
		numofleaves(T->left);
		numofleaves(T->right);
	}
	return count;
}

static int numoffullnode(ExTree T){
	static int count = 0;
	if(T == NULL){
		return 0;
	}else if(T->left && T->right){
		count++;
	}
	numoffullnode(T->left);
	numoffullnode(T->right);
	return count;
}

int main(){
	int i;
	ExTree T;
	T = NULL;
	for(i=32;i>0;i--){
		T = ex_insert(T,i);
	}
	printTree(T);
	printf("\nfind 1:\n");
	T = ex_find(T,1);
	printTree(T);
	printf("\nfind 2:\n");
	T = ex_find(T,2);
	printTree(T);
	printf("\nfind 3:\n");
	T = ex_find(T,3);
	printTree(T);
	printf("\nfind 4:\n");
	T = ex_find(T,4);
	printTree(T);
	printf("\nfind 4:\n");
	T = ex_find(T,4);
	printTree(T);
	printf("\n");
	printf("node:%d,leaves:%d,full:%d\n",numofnodes(T),numofleaves(T),numoffullnode(T));
	return 0;
}
