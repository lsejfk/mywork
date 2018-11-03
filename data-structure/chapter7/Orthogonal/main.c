#include "OrthogonalList.h"

int main(){
	OLGraph graph;
	int i;
	ArcBox *p;
	createDG(&graph);
	for(i=0;i<graph.vexnum;i++){
		printf("position in %d for the out:>\n",i);
		for(p=graph.xlist[i].firstout;p!=NULL;p=p->tlink){
			printf("(%d,%d)\t",p->tailvex,p->headvex);
		}
		printf("\nfor the in:>\n");
		for(p=graph.xlist[i].firstin;p!=NULL;p=p->hlink){
			printf("(%d,%d)\t",p->tailvex,p->headvex);
		}
		printf("**************************************************\n");
	}
	return 0;
}
