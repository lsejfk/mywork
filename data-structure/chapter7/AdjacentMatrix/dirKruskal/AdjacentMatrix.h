#ifndef ADJACENTMATRIX_H
#define ADJACENTMATRIX_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VERTEX_NUM 20			//max vertex number
#define MAX_CH 10
#define INFINITY -1
typedef char VertexType[MAX_CH],*VexPointType;
typedef int VRType;
typedef char InfoType;
typedef enum{DG,DN,UDG,UDN} GraphKind;		//directed graph,directed net,undirected graph,undirected net
typedef struct {
	VRType adj;				//the relationship of vertex
	InfoType *info;				//the information of arc
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//adjacent matrix

typedef struct {
	VertexType vex[MAX_VERTEX_NUM];		//vertex vector
	AdjMatrix arcs;				//adjacent matrix
	int vertexNum;				//the number of vertexes
	int arcNum;				//the number of arc
	GraphKind kind;				//the kind of graph
}MatrixGraph;


void createUDG(MatrixGraph *graph);
void miniSpanTree_prim(MatrixGraph *graph,VertexType vex);
#endif
