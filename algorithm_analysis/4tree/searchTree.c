#include "searchTree.h"
#include <stdio.h>
#include <stdlib.h>

//make empty
SearchTree st_makeEmpty(SearchTree T){
	if(T != NULL){
		st_makeEmpty(T->left);
		st_makeEmpty(T->right);
		free(T);
	}
	return NULL;
}

//find the element in the tree T
STPosition st_find(SearchTreeElemType x,SearchTree T){
	if(T == NULL){
		return NULL;
	}
	if(x < T->data){
		st_find(x,T->left);
	}else if(x > T->data){
		st_find(x,T->right);
	}else{
		return T;
	}
}

//find the max element in the tree
STPostion st_findMax(SearchTree T){
	if(T != NULL){
		while(T->right){
			T = T->right;
		}
		return T;
	}
	return NULL;
}

//find the min element in the tree
STPosition st_findMin(SearchType T){
	if(T != NULL){
		while(T->left){
			T = T->left;
		}
		return T;
	}
	return NULL;
}

//insert x into the tree
SearchTree st_insert(SearchTreeElemType x,SearchTree T){
	STPosition node;
	if(T == NULL){
		node = (SearchTree)malloc(sizeof(struct SearchTreeNode));
		if(node == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		node->data  = x;
		node->left = node->right = NULL;
		return node;
	}
	if(x < T->data){
		T->left = st_insert(x,T->left);
	}else if(x > T->data){
		T->right = st_insert(x,T->right);
	}
	return T;
}

//delete x from the tree
SearchTree st_delete(SearchTreeElemType x,SearchTree T){
	STPosition p;
	if(T == NULL){
		return NULL;
	}
	if(x < T->data){
		T->left = st_delete(x,T->left);
	}else if(x > T->data){
		T->right = st_delete(x,T->right);
	}else{
		if(T->left && T->right){
			//delete the min sub-node
			p = st_findMin(T);
			T->data = p->data;
			T->right = st_delete(p->data,T->right);
		}else{
			p = T;
			if(T->left){
				T = T->left;
			}else if(T->right){
				T = T->right;
			}
			free(p);
		}
	}
	return T;
}


//get the data
SearchTreeElemType st_retrieve(STPosition p){
	if(p == NULL){
		return 0;
	}
	return p->data;
}
