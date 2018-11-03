#include "ThreadBinaryTree.h"

int main(){
	ThreadBinTree *troot,*root;
	createTBinTree(&root);
	inOrderThreading(&troot,root);
	inOrderTraverse_th(troot,visit);
	putchar('\n');
	return 0;
}
