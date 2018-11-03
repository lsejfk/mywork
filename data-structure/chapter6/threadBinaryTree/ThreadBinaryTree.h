#ifndef THREADBINTREE_H
#define THREADBINTREE_H
#include<stdio.h>
#include<stdlib.h>

#define ThBinTreeElemType int
typedef enum{Thread,Link} PointerTag;		//Thread--the node is pointer to thread ;Link--the node is pointer to the link

typedef struct ThreadBinTree{
	ThBinTreeElemType data;			//the element
	struct ThreadBinTree *lchild;
	struct ThreadBinTree *rchild;
	PointerTag lTag;			//the left tag
	PointerTag rTag;			//the right tag
}ThreadBinTree;

void createTBinTree(ThreadBinTree **root);
void inOrderThreading(ThreadBinTree **threadRoot,ThreadBinTree *binRoot);
void visit(ThBinTreeElemType *v);
void inOrderTraverse_th(ThreadBinTree *head,void (*visit)(ThBinTreeElemType *e));

#endif
