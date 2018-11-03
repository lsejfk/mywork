#ifndef KRUSKAL_MFSET_H
#define KRUSKAL_MFSET_H
typedef int VRCost;

typedef struct Arc{
	int i;				//the serial of one vertex
	int j;				//the serial of other vertex
	VRCost weight;			//the cost of the arc
}Arc;				//define the arc type

int inputArcs(Arc **arc);
void miniSpanTree_kruskal(MFSet s,Arc *arc,int arcnum);
#endif
