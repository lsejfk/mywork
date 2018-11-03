#include "AdjacencyList.h"
#include "Stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int CostType;
static void findDegree(ALGraph *graph,int indegree[]);

static  CostType *ve = NULL;						//the array of earliest occuring time
static CostType *vl = NULL;						//the array of latest occur time
static Stack tt;
//topo sort
int topoLogicalOrder(ALGraph *graph){
	int *indegree,i,v,count;
	ArcNode *p;
	Stack st;
	count = 0;
	indegree = (int *)malloc(sizeof(int) * graph->vexnum);	//save information of entry-degree
	assert(indegree != NULL);
	ve = (CostType *)malloc(sizeof(CostType) * graph->vexnum);
	vl = (CostType *)malloc(sizeof(CostType) * graph->vexnum);
	assert(ve != NULL && vl != NULL);
	findDegree(graph,indegree);				//initialize indegree
	initStack(&st);						//initialize stack
	initStack(&tt);

	for(i=0;i<graph->vexnum;i++){				//push 0-entry-degree vertex into stack
		if(indegree[i] == 0){
			stack_push(&st,i);
		}
		ve[i] = vl[i] = 0;
	}
	while(!stack_isEmpty(&st)){
		stack_pop(&st,&v);
		stack_push(&tt,v);				//save the topo serial
		count++;
		//delete arcs related to v
		for(p=graph->alist[v].firstarc;p!=NULL;p=p->nextarc){
			if(--indegree[p->adjvex] == 0){
				stack_push(&st,p->adjvex);		//push the new 0-entry-degree vertexs
			}
			if(ve[v] + *(p->info) > ve[p->adjvex]){	//the maxmum cost
				ve[p->adjvex] = ve[v] + *(p->info);
			}
		}
	}
	if(count < graph->vexnum){
		return 0;
	}
	return 1;
}

//output the critical path
int criticalPath(ALGraph *graph){
	int i,j;
	ArcNode *p;
	CostType ne,nl;
	char tag;
	if(topoLogicalOrder(graph) == 0){
		return 0;
	}
	for(i=0;i<graph->vexnum;i++){
		vl[i] = ve[graph->vexnum-1];							//initialize vl
	}
	for(i=0;i<graph->vexnum;i++){						//find the inverse topological serials
		for(stack_pop(&tt,&j),p=graph->alist[j].firstarc;p!=NULL;p=p->nextarc){
			if(vl[j] > vl[p->adjvex] - *(p->info)){
				vl[j] = vl[p->adjvex] - *(p->info);
			}
		}
	}
	for(i=0;i<graph->vexnum;i++){
		for(p=graph->alist[i].firstarc;p!=NULL;p=p->nextarc){
			ne = ve[i];						//earliest start time
			nl = vl[p->adjvex] - *(p->info);			//latest start time
			tag = ne == nl ? '*' : ' ';
			printf("%c--%d-->%d,dut=%d,ne=%d,nl=%d\n",tag,i,p->adjvex,*(p->info),ne,nl);
		}
	}
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
