#ifndef BINTREE_H
#define BINTREE_H
#include<stdio.h>
#include<stdlib.h>
#define BinTreeElemType int

typedef struct BinTree{
	BinTreeElemType data;
	struct BinTree *lchild;
	struct BinTree *rchild;
}BinTree;

void visit(BinTreeElemType *e);
void initBinTree(BinTree **root);
void createBinTree(BinTree **root);		//create the binary tree in preorder
void inOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e));
void preOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e));
void postOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e));

#endif
