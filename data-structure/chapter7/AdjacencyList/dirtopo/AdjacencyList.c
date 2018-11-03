#include "AdjacencyList.h"
#include "LinkStack.h"
#include "CyclicQueue.h"
#include<stdio.h>
#include<stdlib.h>

//buy node
ArcNode *buynode(){
	ArcNode *qv;
	qv = (ArcNode *)malloc(sizeof(ArcNode));		//allocate for the arc
	if(qv == NULL){
		fprintf(stderr,"error:buynode:malloc qv failed\n");
		return NULL;
	}
	qv->nextarc = NULL;
	qv->info = NULL;
//	qv->adjvex = adj;
	return qv;
}
//create the Adjacency List
void createALG(ALGraph *ax,GraphType type){
	int i,j,nvex,narc,e,v,w;
	ArcNode *qv,*qw;
	VexNode *p;
	scanf("%d%d",&nvex,&narc);
	p = (VexNode *)malloc(sizeof(VexNode) * nvex);		//allocate for the vertex
	if(p == NULL){
		fprintf(stderr,"error:createALG:malloc p failed\n");
		return;
	}
	//initialize the vertex list
	for(i=0;i<nvex;i++){
		scanf("%d",&e);
		p[i].data = e;
		p[i].firstarc = NULL;
	}
	ax->alist = p;
	ax->vexnum = nvex;
	ax->arcnum = narc;
	//input the arc
	for(i=0;i<narc;i++){
		scanf("%d%d",&v,&w);
		qv = buynode();
		qv->adjvex = w;			//note:I made a mistake at this point
		qv->nextarc = p[v].firstarc;
		p[v].firstarc = qv;
		if(type == UDG){
			qw = buynode();
			qw->adjvex = v;
			qw->nextarc = p[w].firstarc;
			p[w].firstarc = qw;
		}
	//	printf("i=%d (%d %d)\n",i,v,w);
	}
}

//visit the node
void visit(VertexType *e){
	printf("%4d",*e);
}

//depth first search
void depthFirstSearch(ALGraph *ax,void (*visit)(VertexType *)){
	LinkStack st;
	int *visited,i;
	ArcNode *p;
	initLinkStack(&st);
	visited = (int *)malloc(sizeof(int) * ax->vexnum);
	if(visited == NULL){
		fprintf(stderr,"error:depthFirstSearch:malloc visited faild\n");
		return;
	}
	for(i=0;i<ax->vexnum;i++){
		visited[i] = 0;			//haven't been visited
	}
	/*
	for(i=0;i<ax->vexnum;i++){
		if(!visited[i]){		//haven't been visited
			visited[i] = 1;
			visit(&(ax->alist[i].data));	//visit the vertex
			p = ax->alist[i].firstarc;
			if(p != NULL && !visited[p->adjvex]){
				visited[p->adjvex] = 1;
				visit(&(ax->alist[p->adjvex].data));
				push(&st,p);

				do{
					while(p != NULL && !visited[p->adjvex]){
						visited[p->adjvex] = 1;
						visit(&(ax->alist[p->adjvex].data));
						push(&st,p);
						p = ax->alist[p->adjvex].firstarc;	//p point to the vertex
					}
					pop(&st,&p);
					p = p->nextarc;
				}while(p != NULL || !isEmpty(&st));
			}
		}
	}
	*/
	for(i=0;i<ax->vexnum;i++){
		if(!visited[i]){
			visited[i] = 1;
			visit(&(ax->alist[i].data));
			push(&st,ax->alist[i].firstarc);
			while(!isEmpty(&st)){
				while((getTop(&st,&p),p != NULL) && !visited[p->adjvex]){
					visited[p->adjvex] = 1;
					visit(&(ax->alist[p->adjvex].data));
					push(&st,ax->alist[p->adjvex].firstarc);
				}
				pop(&st,&p);			//pop the useless node
				if(!isEmpty(&st)){
					pop(&st,&p);
					push(&st,p->nextarc);	//go to the next arc
				}
			}
		}
	}
}


//Broadth First Search
void broadFSearch(ALGraph *graph,void (*visit)(VertexType *)){
	int *visited,i;
	CyclicQ queue;
	ArcNode *p;
	visited = (int *)malloc(sizeof(int) * graph->vexnum);
	if(visited == NULL){
		fprintf(stderr,"error:broadFSearch:malloc visited failed\n");
		return;
	}
	for(i=0;i<graph->vexnum;i++){
		visited[i] = 0;	
	}
	initCyclicQ(&queue,graph->vexnum+1);		//initialize the queue
	for(i=0;i<graph->vexnum;i++){
		if(!visited[i]){			//this vertex hasn't been visited
			visited[i] = 1;
			visit(&(graph->alist[i].data));	//visit the vertex
			p = graph->alist[i].firstarc;
			while(p != NULL || !isQueueEmpty(&queue)){
				if(p != NULL){		//traverse all of arc of the vertex
					do{
						if(!visited[p->adjvex]){
							visited[p->adjvex] = 1;
							visit(&(graph->alist[p->adjvex].data));
							enQueue(&queue,p);
						}
						p = p->nextarc;
					}while(p != NULL);//while
				}else{			//go to the next layer
					deQueue(&queue,&p);
					p = graph->alist[p->adjvex].firstarc;	
				}
			}//while
		}//if
	}//for
}



