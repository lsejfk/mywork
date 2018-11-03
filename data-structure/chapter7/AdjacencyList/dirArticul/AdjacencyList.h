#ifndef ADJACENCY_H
#define ADJACENCY_H
#include<stdio.h>
#include<stdlib.h>
#define InfoType int
#define VertexType int
typedef struct ArcNode{
	int adjvex;		//the position of the vertex to which the arc points
	struct ArcNode *nextarc;	//point to the next arc
	InfoType *info;		//the information of the arc
}ArcNode;

typedef struct VexNode{
	VertexType data;	//the data of the vertex
	ArcNode *firstarc;	//a pointer to the first arc attached to the vertex
}VexNode;

typedef struct ALGraph{
	int vexnum;		//the number of vertex
	int arcnum;		//the number of arc
	VexNode *alist;		//the pointer to an array of vertex,it will be initialized by createALG()
}ALGraph;

void createALG(ALGraph *alist);
void visit(VertexType *e);	//visit the node
void depthFirstSearch(ALGraph *ax,void (*visit)(VertexType *));		//depth first search
void broadFSearch(ALGraph *graph,void (*visit)(VertexType *));		//broadth First Search

#endif
