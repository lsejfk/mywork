#include "balancedBinaryTree.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
	int data,i,n,taller;
	BSTree t,s;
	n = 6;
	taller = 0;
	initBinTree(&t);
	initBinTree(&s);
	printf("First Order\n");
	for(i=0;i<n;i++){
		scanf("%d",&data);
		insertAVL(&t,data,&taller);
	}
	inOrderTraverse(t,visit);
	printf("\n");
	taller = 0;
	for(i=0;i<n;i++){
		scanf("%d",&data);
		insertAVL(&s,data,&taller);
	}
	inOrderTraverse(s,visit);
	printf("\n");
}
