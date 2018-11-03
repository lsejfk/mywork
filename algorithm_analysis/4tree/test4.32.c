#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>

static AvlTree buildTree(int height){
	static int n = 1;
	AvlTree T = NULL;
	if(height >= 0){
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if(T == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		T->left = buildTree(height - 1);
		T->elem = n++;
		T->height = height;
		T->right = buildTree(height - 1);
		return T;
	}
	return NULL;
}

static void printTree(AvlTree T){
	if(T){
		printTree(T->left);
		printf("(%d,%d) ",T->elem,T->height);
		printTree(T->right);
	}
}

static void printElem(AvlTree T,AvlElemType k1,AvlElemType k2){
	if(k1 > k2){
		return;
	}
	if(T){
		if(k1 <= T->elem && k2 >= T->elem){
			printElem(T->left,k1,T->elem);
			printf("%d ,",T->elem);
			printElem(T->right,T->elem,k2);
		}else if(k1 > T->elem){
			printElem(T->right,k1,k2);
		}else{
			printElem(T->left,k1,k2);
		}
	}
}

int main(){
	AvlTree T;
	T = buildTree(5);
	printElem(T,10,20);
	return 0;
}
