#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H
#include "BinTreeStruct.h"

int searchBST(BinTree *t,BinTreeElemType key,BinTree *f,BinTree **p);
int insertBST(BinTree **t,BinTreeElemType data);
int deleteNode(BinTree **p);
int deleteBST(BinTree **t,BinTreeElemType key);
#endif
