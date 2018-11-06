#include "adjlist.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void topsort(AlGraph G);

int main(){
	AlGraph G;
	G = graph_create(DG,7,12);
	topsort(G);
	return 0;
}

void topsort(AlGraph G){
	Stack S;
	int *indegree;
	int i;
	ArcPtr p;

	S = arr_createStack(G->vexnum);
	indegree = (int *)calloc(G->vexnum,sizeof(int));
	if(indegree == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	for(i=0;i<G->vexnum;i++){
		indegree[i] = 0;
	}
	for(i=0;i<G->vexnum;i++){
		for(p=G->vertices[i].firstarc;p;p=p->next){
			indegree[p->adjvex]++;
		}
	}
	for(i=0;i<G->vexnum;i++){
		if(indegree[i] == 0){
			arr_push(i,S);
		}
	}
	while(!arr_isEmpty(S)){
		i = arr_topAndPop(S);
		printf("%s->",G->vertices[i].data->name);
		for(p=G->vertices[i].firstarc;p;p=p->next){
			if(--indegree[p->adjvex] == 0){
				arr_push(p->adjvex,S);
			}
		}
	}

}
