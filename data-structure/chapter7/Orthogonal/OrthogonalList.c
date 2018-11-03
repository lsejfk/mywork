#include "OrthogonalList.h"

//create the Orthogonal List
void createDG(OLGraph *olGraph) {
	int i,j,nvex,narc,e,k,v,w;
	VexNode *p;
	ArcBox *q,*pre,*cur;
	scanf("%d%d",&nvex,&narc);		//input the number of vertex and arc
	p = (VexNode *)malloc(sizeof(VexNode) * nvex);		//allocate for the array of vertex
	if(p == NULL){
		fprintf(stderr,"eroor:createDG:malloc VexNode failed\n");
		return;
	}
	//initialize the array
	for(i=0;i<nvex;i++){
		scanf("%d",&e);
		p[i].data = e;
		p[i].firstin = p[i].firstout = NULL;
	}
	//initialize the graph
	olGraph->xlist = p;
	olGraph->vexnum = nvex;
	olGraph->arcnum = narc;
	//input the arc infomation and create the Orthogonal List
	for(k=0;k<narc;k++){
		scanf("%d%d",&v,&w);				//input the position of vertex in the graph
		q = (ArcBox *)malloc(sizeof(ArcBox));		//create the arc node
		q->tailvex = v;
		q->headvex = w;
		q->hlink = q->tlink = NULL;
		q->info = NULL;
		//insert the line
		pre = NULL;
		cur = p[v].firstout;
		while(cur != NULL && cur->headvex < w){
			pre = cur;
			cur = cur->tlink;
		}
		if(pre == NULL){				//the firstout node
			q->tlink = NULL;
			p[v].firstout = q;
		}else{
			q->tlink = pre->tlink;
			pre->tlink = q;
		}
		//insert the column
		pre = NULL;
		cur = p[w].firstin;
		while(cur != NULL && cur->tailvex < v){		//find the position for inserting
			pre = cur;
			cur = cur->hlink;
		}
		if(pre == NULL){				//the firstin node
			q->hlink = NULL;
			p[w].firstin = q;
		}else{
			q->hlink = pre->hlink;
			pre->hlink = q;
		}
	}
}
