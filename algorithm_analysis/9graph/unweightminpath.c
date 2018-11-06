#include "adjlist.h"
#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void graph_uwminpath(AlGraph G,PRTable T);

int main(){
	AlGraph G;
	PRTable T;
	int i;
	G = graph_create(DG,7,12);
	T = prt_create(7,2);
	graph_uwminpath(G,T);
	for(i=0;i<G->vexnum;i++){
		prt_printThePath(G,T,2,i);
	}
	return 0;
}

//find the minimum path from unweighted graph
void graph_uwminpath(AlGraph G,PRTable T){
	int v;
	ArrQueue Q;
	ArcPtr p;
	Q = arrque_createQueue(G->vexnum);
	arrque_makeEmpty(Q);
	
	//enqueue the start point
	arrque_enqueue(T->startindex,Q);
	while(!arrque_isEmpty(Q)){
		v = arrque_frontAndDequeue(Q);
		T->list[v].known = 1;

		for(p=G->vertices[v].firstarc;p;p=p->next){
			if(T->list[p->adjvex].dist == INFINITE){
				T->list[p->adjvex].dist = T->list[v].dist + 1;
				T->list[p->adjvex].path = v;
				arrque_enqueue(p->adjvex,Q);
			}//if
		}//for
	}//while

	arrque_disposeQueue(Q);
}
