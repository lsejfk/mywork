#ifndef ORTHOGONAL_H
#define ORTHOGONAL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define InfoType int
#define VertexType int

typedef struct ArcBox{
	int tailvex;		//the position of the tail vertex of the arc
	int headvex;		//the position of the head vertex of the arc
	struct ArcBox *hlink;	//chain domain with the same arc head
	struct ArcBox *tlink;	//chain domain with the same arc tail
	InfoType *info;		//the information of the arc
}ArcBox;	//the arc node

typedef struct VexNode{
	VertexType data;	//the data of the Vertex
	ArcBox *firstin;	//the first entry arc
	ArcBox *firstout;	//the first arc
}VexNode;	//the vertex node

typedef struct OLGraph{
	VexNode *xlist;		//the array of vertex,it will be initialized in createDG() function
	int vexnum;		//the number of vertext
	int arcnum;		//the number of arc
}OLGraph;


void createDG(OLGraph *olGra);		//create the Orthogonal List

#endif
