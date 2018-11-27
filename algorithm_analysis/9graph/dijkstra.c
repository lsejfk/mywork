#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjlist.h"
struct heapelem_tag{
	int index;
	int dist;
};
#define HEAPTYPE struct heapelem_tag
#include "priorityqueue.h"

//static int find_mindist(PRTable T);
void dijkstra(AlGraph G,PRTable T);

int comp(const void *a,const void *b){
	return (((struct heapelem_tag *)a)->dist - ((struct heapelem_tag *)b)->dist);
}

int main(){
	AlGraph G;
	PRTable T;
	int i;
	G = graph_create(DGW,7,12);
	T = prt_create(7,0);
	dijkstra(G,T);
	for(i=0;i<G->vexnum;i++){
		prt_printThePath(G,T,T->startindex,i);
	}
	return 0;
}

void dijkstra(AlGraph G,PRTable T){
	PriorityQueue H;
	HeapElemType e,k;
	ArcNode p;
	int v,w;
	H = priq_init(T->size);
	e.index = T->startindex;
	e.dist = T->list[T->startindex].dist;
	priq_insert(e,H,comp);

	while(!priq_isEmpty(H)){
		//find the unkown vertex
		do{
			k = priq_deleteMin(H,comp);
			v = k.index;
		}while(!priq_isEmpty(H) && T->list[v].known);
		T->list[v].known = 1;
		for(p=G->vertices[v].firstarc;p;p=p->next){
			w = p->adjvex;
			if(T->list[w].known == 0){
				if(T->list[v].dist + p->info->weight < T->list[w].dist){
					//enqueue
					e.index = w;
					e.dist = T->list[v].dist + p->info->weight;
					T->list[w].dist = e.dist;
					priq_insert(e,H,comp);
					T->list[w].path = v;
				}//if
			}//if
		}//for
	}//while
}
        
/*

void dijkstra(AlGraph G,PRTable T){
	int v,w;
	ArcNode p;
	for(;;){
		v = find_mindist(T);
		if(v < 0){	//no path
			break;
		}
		T->list[v].known = 1;
		for(p=G->vertices[v].firstarc;p;p=p->next){
			w = p->adjvex;
			if(T->list[w].known == 0){
				if(T->list[v].dist + p->info->weight < T->list[w].dist){
					T->list[w].dist = T->list[v].dist + p->info->weight;
					T->list[w].path = v;
				}//if
			}//if T
		}//for
	}//for
}

static int find_mindist(PRTable T){
	int i,res;
	int min;
	if(T == NULL){
		fprintf(stderr,"T is NULL in find_mindist\n");
		return -1;
	}
	min = INFINITE;
	res = -1;
	for(i=0;i<T->size;i++){
		if(T->list[i].known == 0){
			if(T->list[i].dist < min){
				min = T->list[i].dist;
				res = i;
			}
		}
	}
	return res;
}
*/
