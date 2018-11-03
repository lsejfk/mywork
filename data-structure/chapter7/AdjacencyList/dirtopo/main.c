#include "AdjacencyList.h"
#include "topoLogicalSort.h"
#include<stdio.h>

int main(void){
	ALGraph graph;
	createALG(&graph,DG);
	topoLogicalSort(&graph);
	//printf("hello\n");
	return 0;
}
