#ifndef DFSFOREST_H
#define DFSFOREST_H
#include "AdjacencyList.h"
#define ChildBroListType VertexType
typedef struct ChildBroList{
	ChildBroListType data;
	struct ChildBroList *firstchild;		//the child node
	struct ChildBroList *nextsibling;		//the brother node
}ChildBroList;

void visit(ChildBroListType *e);
void preOrderTraverse(ChildBroList *root,void (*visit)(ChildBroListType *e));

//create Child Brother List T of generatint forest of undirected graph g in depth priority way 
void DFSForest(ALGraph *graph,ChildBroList **hlist);

#endif
