#include "BinTreeStruct.h"
#include "LinkStack.h"
int main(){
	BinTree *root;
	initBinTree(&root);
	createBinTree(&root);
	printf("the inOrder:\n");
	inOrderTraverse(root,visit);
	putchar('\n');
	printf("the preOrder:\n");
	preOrderTraverse(root,visit);
	putchar('\n');
	printf("the postOrdre:\n");
	postOrderTraverse(root,visit);
	putchar('\n');

	return 0;
}
