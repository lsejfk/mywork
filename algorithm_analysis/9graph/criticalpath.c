#include "adjlist.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int criticalpath(AlGraph G);
static int topologicalpath(AlGraph G,Stack T,int *ve);

int main(){
	AlGraph G;

	G = graph_create(DGW,9,11);
	if(criticalpath(G) < 0){
		fprintf(stderr,"the graph don't have critical path\n");
		return -1;
	}
	return 0;
}

static int criticalpath(AlGraph G){
	int *ve,*vl;
	int i,j,k;
	Stack T;
	ArcNode p;
	T = arr_createStack(G->vexnum);
	ve = (int *)calloc(G->vexnum,sizeof(int));
	vl = (int *)calloc(G->vexnum,sizeof(int));
	if(ve == NULL || vl == NULL){
		fprintf(stderr,"calloc failed\n");
		return -1;
	}
	for(i=0;i<G->vexnum;i++){
		ve[i] = 0;
		vl[i] = 0;
	}
	if(topologicalpath(G,T,ve) < 0){
		return -1;
	}
	//initialize array vl
	for(i=0;i<G->vexnum;i++){
		vl[i] = ve[i];
	}
	while(!arr_isEmpty(T)){
		j = arr_topAndPop(T);
		for(p=G->vertices[j].firstarc;p;p=p->next){
			k = p->adjvex;
			if(vl[k] - p->info->weight < vl[j]){
				vl[j] = vl[k] - p->info->weight;
			}
		}
	}

	for(i=0;i<G->vexnum;i++){
		for(p=G->vertices[i].firstarc;p;p=p->next){
			k = p->adjvex;
			if(ve[i] == vl[k] - p->info->weight){
				printf("%s->%s,",G->vertices[i].data->name,G->vertices[k].data->name);
			}
		}
	}
	return 0;
}

static int topologicalpath(AlGraph G,Stack T,int *ve){
	int i,j;
	int *indegree;
	Stack S;
	ArcNode p;

	S = arr_createStack(G->vexnum);
	indegree = (int *)calloc(G->vexnum,sizeof(int));
	if(indegree == NULL){
		fprintf(stderr,"calloc failed\n");
		return -1;
	}
	for(i=0;i<G->vexnum;i++){
		indegree[i] = 0;
	}

	//find the verteies whose indegree equal to zero
	for(i=0;i<G->vexnum;i++){
		for(p=G->vertices[i].firstarc;p;p=p->next){
			j = p->adjvex;
			indegree[j]++;
		}
	}
	for(i=0;i<G->vexnum;i++){
		if(indegree[i] == 0){
			arr_push(i,S);
		}
	}
	while(!arr_isEmpty(S)){
		i = arr_topAndPop(S);
		arr_push(i,T);
		for(p=G->vertices[i].firstarc;p;p=p->next){
			j = p->adjvex;
			if(ve[i] + p->info->weight > ve[j]){
				ve[j] = ve[i] + p->info->weight;
			}
			if(--indegree[j] == 0){
				arr_push(j,S);
			}
		}
	}
	if(arr_isEmpty(T)){
		return -1;
	}
	return 0;
}
