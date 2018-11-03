#include "AdjacencyList.h"
#include "Stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
static void findDegree(ALGraph *graph,int indegree[]);
//topo sort
int topoLogicalSort(ALGraph *graph){
	int *indegree,i,v,count;
	ArcNode *p;
	Stack st;
	count = 0;
	indegree = (int *)malloc(sizeof(int) * graph->vexnum);	//save information of entry-degree
	assert(indegree != NULL);
	findDegree(graph,indegree);				//initialize indegree
	initStack(&st);						//initialize stack
	for(i=0;i<graph->vexnum;i++){				//push 0-entry-degree vertex into stack
		if(indegree[i] == 0){
			stack_push(&st,i);
		}
	}
	while(!stack_isEmpty(&st)){
		stack_pop(&st,&v);
		printf("%d\n",graph->alist[v].data);
		count++;
		//delete arcs related to v
		for(p=graph->alist[v].firstarc;p!=NULL;p=p->nextarc){
			if(--indegree[p->adjvex] == 0){
				stack_push(&st,p->adjvex);		//push the new 0-entry-degree vertexs
			}
		}
	}
	if(count < graph->vexnum){
		return 0;
	}
	return 1;
}

//find the entry degree of each vertex
static void findDegree(ALGraph *graph,int indegree[]){
	int i;
	ArcNode *p;
	for(i=0;i<graph->vexnum;i++){
		indegree[i] = 0;
	}
	for(i=0;i<graph->vexnum;i++){
		for(p=graph->alist[i].firstarc;p != NULL;p=p->nextarc){
			indegree[p->adjvex]++;
		}
	}
}
