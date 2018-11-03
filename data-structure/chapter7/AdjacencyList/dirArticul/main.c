#include "ArticulationPoint.h"
#include "AdjacencyList.h"

int main(void){
	ALGraph graph;
	createALG(&graph);
	findArticul(&graph);
//	print(&graph);
	return 0;
}
