#include "adjlist.h"
#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>
static void weightNegative(AlGraph G,PRTable T);

int main(){
	AlGraph G;
	PRTable T;
	int i;
	G = graph_create(DGW,7,12);
	T = prt_create(G->vexnum,0);
	weightNegative(G,T);
	for(i=0;i<G->vexnum;i++){
		prt_printThePath(G,T,T->startindex,i);
	}
	return 0;
}

static void weightNegative(AlGraph G,PRTable T){
	ArrQueue Q;
	ArcNode p;
	int v,w;
	Q = arrque_createQueue(G->vexnum);
	arrque_enqueue(T->startindex,Q);
	while(!arrque_isEmpty(Q)){
		v = arrque_frontAndDequeue(Q);
		T->list[v].known *= -1;		//dequeue
		T->list[v].known++;
		if(T->list[v].known > G->vexnum){
			break;
		}
		for(p=G->vertices[v].firstarc;p;p=p->next){
			w = p->adjvex;
			if(T->list[v].dist + p->info->weight < T->list[w].dist){
				T->list[w].dist = T->list[v].dist + p->info->weight;
				T->list[w].path = v;
				if(T->list[w].known > 0){	//not in queue
					arrque_enqueue(w,Q);
					T->list[w].known *= -1;
				}
			}
		}
	}
	arrque_disposeQueue(Q);
}
