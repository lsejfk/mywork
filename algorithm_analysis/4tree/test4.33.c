#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

static BinTree buildTree(int height){
	static int n = 1;
	BinTree T = NULL;
	if(height >= 0){
		T = (BinTree)malloc(sizeof(struct BinTreeNode));
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
/*

static void printTree(BinTree T){
	if(T){
		printTree(T->left);
		printf("(%d,%d,%d) ",T->x,T->y,T->elem);
		printTree(T->right);
	}
}

static void printBinTree(BinTree T){
	if(T){
		printBinTree(T->left);

	}
}

static void setLocation(BinTree T,int x,int y){
	if(T){
		T->x = x;
		T->y = y;
		setLocation(T->left,x-1,y+1);
		setLocation(T->right,x+1,y+1);
	}
}
*/
static void print(BinTree T){
	ArrQueue Q;
	BinTreePtr p;
	Q = arrque_createQueue(100);
	if(T == NULL){
		return;
	}
	arrque_enqueue(T,Q);
	while(!arrque_isEmpty(Q)){
		p = arrque_frontAndDequeue(Q);
		printf("%d,",p->elem);
		if(p->left){
			arrque_enqueue(p->left,Q);
		}
		if(p->right){
			arrque_enqueue(p->right,Q);
		}
	}
	printf("end\n");
}

int main(){
	BinTree T;
	T = buildTree(5);
	print(T);
	return 0;
}
