#include "AdjacencyList.h"
#include "criticalPath.h"
#include<stdio.h>

int main(void){
	ALGraph graph;
	createALG(&graph,DG);
	criticalPath(&graph);
	//printf("hello\n");
	return 0;
}
