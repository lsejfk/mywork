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

int main(){
	AvlTree T;
	T = buildTree(5);
	printTree(T);
	printf("\n");
}
