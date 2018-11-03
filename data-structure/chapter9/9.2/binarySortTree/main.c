#include "binarySortTree.h"

int main(){
	BinTree *t;
	int n = 7;
	BinTreeElemType data;
	initBinTree(&t);
	while(n-- > 0){
		scanf("%d",&data);
		insertBST(&t,data);
	}
	inOrderTraverse(t,visit);
	deleteBST(&t,12);
	putchar('\n');
	inOrderTraverse(t,visit);
}
