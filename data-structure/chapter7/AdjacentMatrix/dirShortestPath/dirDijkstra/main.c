#include "AdjacentMatrix.h"
#include "Dijkstra.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
int main(){
	MatrixGraph graph;
	VRType *dij;
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int i,j;
	createMG(&graph,DG);
	dij = (VRType *)malloc(sizeof(VRType) * graph.vertexNum);
	assert(dij != NULL);
	shortestPath_Dij(&graph,0,dij,path);
	for(i=0;i<graph.vertexNum;i++){
		printf("i=%d\t",dij[i]);
	}
	for(i=0;i<graph.vertexNum;i++){
		printf("\n");
		for(j=0;j<graph.vertexNum;j++){
			printf("%2d",path[i][j]);
		}
	}
	return 0;
}
