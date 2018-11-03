#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

//return the the height of the tree
int avl_height(AvlTree T){
	if(T == NULL){
		return -1;
	}else{
		return T->height;
	}
}

//make empty
AvlTree avl_makeEmpty(AvlTree T){
	if(T == NULL){
		return NULL;
	}
	if(T->left == NULL && T->right == NULL){
		free(T);
		return NULL;
	}
	if(T->left){
		T->left = avl_makeEmpty(T->left);
	}
	if(T->right){
		T->right = avl_makeEmpty(T->right);
	}
	return T;
}

//find element x int tree T
AvlPosition avl_find(AvlElemType x,AvlTree T){
	if(T != NULL){
		if(x < T->elem){
			return avl_find(x,T->left);
		}else if(x > T->elem){
			return avl_find(x,T->right);
		}
	}
	return T;
}

//find the minimum element in the tree
AvlPosition avl_findMin(AvlTree T){
	if(T != NULL){
		while(T->left){
			T = T->left;
		}
	}
	return T;
}


//find the maximum element in the tree
AvlPostion avl_findMax(AvlTree T){
	if(T != NULL){
		while(T->right){
			T = T->right;
		}
	}
	return T;
}


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
	T->height = max(avl_height(T->left),avl_heigth(T->right)) + 1;
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

//insert into T
AvlTree avl_insert(AvlElemType x,AvlTree T){
	if(T != NULL){
		if(x < T->elem){
			T->left = avl_insert(x,T->left);
			if(avl_height(T->left) - avl_height(T->right) == 2){
				if(x < T->left->elem){
					T = singleRolateLeft(T);
				}else if(x > T->right->elem){
					T = doubleRolateLeft(T);
				}
			}//if
		}else if(x > T->elem){
			T->right = avl_insert(x,T->right);
			if(avl_height(T->right) - avl_height(T->left) == 2){
				if(x < T->right->elem){
					T  = doubleRolateRight(T);
				}else if(x > T->right->elem){
					T = singleRolateRight(T);
				}
			}//if
		}
	}else{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if(T == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		T->elem = x;
		T->height = 0;
		T->left = T->right = NULL;
	}
	return T;
}

/*
//delete element x from tree T
AvlTree avl_delete(AvlElemType x,AvlTree T){
	
}
*/

//return the element
AvlElemType avl_retrieve(AvlPosition p){
	if(p == NULL){
		return 0;
	}
	return p->elem;
}
