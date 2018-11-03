//#include "AdjacentMatrix.h"
#include "MFSet.h"
#include "Kruskal_MFSet.h"
#include<stdio.h>
int main(void){
/*	MatrixGraph graph;
	createUDG(&graph);
	//printf("%s\n",graph.vex[1]);
	miniSpanTree_prim(&graph,"v1");
*/
	MFSet s;
	Arc *arc;
	int arcnum;
	initMFSet(s);
	arcnum = inputArcs(&arc);
	miniSpanTree_kruskal(s,arc,arcnum);
	return 0;
}
