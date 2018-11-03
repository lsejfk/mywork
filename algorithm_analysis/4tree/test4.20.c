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


//get type:1-left-left,2-left-right,3-right-right,4-right-left
static int gettype(AvlTree T){
	AvlPosition p;
	int llc,lrc,rrc,rlc;
	llc = lrc = rrc = rlc = 0;
	if(T == NULL){
		return 0;
	}
	if(T->left){
		p = T->left;
		llc = avl_height(p->left) + 2;
		lrc = avl_height(p->right) + 2;
	}else{
		llc = lrc = 0;
	}
	if(T->right){
		p = T->right;
		rrc = avl_height(p->right) + 2;
		rlc = avl_height(p->left) + 2;
	}else{
		rrc = rlc = 0;
	}
	if(llc > lrc){
		if(rrc > rlc){
			if(llc - rrc == 2){
				return 1;
			}else if(rrc - llc == 2){
				return 3;
			}else{
				return 0;
			}
		}else{
			if(llc - rlc == 2){
				return 1;
			}else if(rlc - llc == 2){
				return 4;
			}else{
				return 0;
			}
		}
	}else{
		if(rrc > rlc){
			if(lrc - rrc == 2){
				return 2;
			}else if(rrc - lrc == 2){
				return 3;
			}else{
				return 0;
			}
		}else{
			if(lrc - rlc == 2){
				return 2;
			}else if(rlc - lrc == 2){
				return 4;
			}else{
				return 0;
			}
		}//if rrc
	}//if llc
}


AvlTree avl_delete(AvlElemType x,AvlTree T){
	Stack S;
	AvlPosition p,q,f;
	int type;

	S = arr_createStack(100);
	//find element x
	p = T;
	while(p){
		arr_push(p,S);
		if(x < p->elem){
			p = p->left;
		}else if(x > p->elem){
			p = p->right;
		}else{
			break;
		}
	}
	if(p == NULL){
		arr_disposeStack(S);
		return T;
	}
	if(p->left && p->right){
		//find the minimum element in the right subtree
		q = p->right;
		while(q){
			arr_push(q,S);
			q = q->left;
		}
		q = arr_topAndPop(S);
		f = arr_top(S);
		if(f == p){
			p->elem = q->elem;
			p->right = q->right;
		}else{
			p->elem = q->elem;
			f->left = q->right;
		}
		free(q);
		//change the height and adjust the balance
		while(!arr_isEmpty(S)){
			q = arr_topAndPop(S);
			q->height = max(avl_height(q->left),avl_height(q->right)) + 1;
			if(abs(avl_height(q->left) - avl_height(q->right)) == 2){
				type = gettype(q);
				if(!arr_isEmpty(S)){
					f = arr_top(S);
					if(f->left == q){
						f->left = doRolate(q,type);
					}else{
						f->right = doRolate(q,type);
					}
				}else{
					f = doRolate(q,type);
					arr_disposeStack(S);
					return f;
				}
			}//if abs
		}//while
	}else{
		q = p;
		arr_pop(S);
		if(p->left != NULL){
			p = p->left;
		}else if(p->right != NULL){
			p = p->right;
		}else{
			p = NULL;
		}
		if(arr_isEmpty(S)){
			arr_disposeStack(S);
			return NULL;
		}else{
			f = arr_top(S);
			if(f->left == q){
				f->left = p;
			}else if(f->right == q){
				f->right = p;
			}
		}
		free(q);

		while(!arr_isEmpty(S)){
			q = arr_topAndPop(S);
			q->height = max(avl_height(q->left),avl_height(q->right)) + 1;
			if(abs(avl_height(q->left) - avl_height(q->right)) == 2){
				type = gettype(q);
				if(!arr_isEmpty(S)){
					f = arr_top(S);
					if(f->left == q){
						f->left = doRolate(q,type);
					}else{
						f->right = doRolate(q,type);
					}
				}else{
					f = doRolate(q,type);
					arr_disposeStack(S);
					return f;
				}
			}//if abs
		}//while
	}//if
	arr_disposeStack(S);
	return T;
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
			type = gettype(p);		//get the inserting type
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
	printf("\n");
	T = avl_delete(10,T);
	printTree(T);
	printf("\n");
	T = avl_delete(1,T);
	printTree(T);
	printf("\n");
	T = avl_delete(16,T);
	printTree(T);
	printf("\n");
}

