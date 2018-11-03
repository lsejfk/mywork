#include "ArticulationPoint.h"
/*
usage:find the articulation point of the graph in Adjacency List Form
*/
static int count = 0;						//the serial of traversing
static int *visited = NULL;					//an array of serial

/*
low[v] = min{visited[v],visited[k],low[w]}
k is the serial of ancestor for v
w is the child of v
(v,w),(v,k) are arcs
*/
static int *low = NULL;						//an array 

static void DFSArticul(ALGraph *,int);

static void init(ALGraph *graph){						//initialization
	visited = (int *)malloc(sizeof(int) * graph->vexnum);		//create an array
	assert(visited != NULL);
	low = (int *)malloc(sizeof(int) * graph->vexnum);
	assert(low != NULL);
}
void findArticul(ALGraph *graph){
	int v,i;
	ArcNode *p;
	init(graph);						//initialize visited and low
	visited[0] = 1;						//the first vertex
	count = 1;						//the serial of traversing
	for(i=1;i<graph->vexnum;i++){				//initialize visited
		visited[i] = 0;					//haven't been visited
	}
	v = graph->alist[0].firstarc->adjvex;
	DFSArticul(graph,v);					//depth-first Search from vertex v
	if(count < graph->vexnum){				//the root has at least two childs
		printf("%d\n",graph->alist[0].data);		//output the articulation point
		p = graph->alist[0].firstarc;
		while(p->nextarc != NULL){			//depth-first search the next vertexs
			p = p->nextarc;
			v = p->adjvex;
			if(visited[v] == 0){			//haven't been visited
				DFSArticul(graph,v);
			}
		}//while
			
	}//if

}

static void DFSArticul(ALGraph *graph,int adj){
	int min,w;
	ArcNode *p;
	visited[adj] = min = ++count;
	for(p = graph->alist[adj].firstarc;p != NULL;p=p->nextarc){	//traverse all the arc
		w = p->adjvex;
		if(visited[w] == 0){				//haven't been visited
			DFSArticul(graph,w);
			if(low[w] < min){
				min = low[w];
			}
			if(low[w] >= visited[adj]){		//there are no back edge
				printf("%d\n",graph->alist[adj].data);	//find an articulation point
			}
		}else if(visited[w] < min){
			min = visited[w];
		}
	}//for
	low[adj] = min;
}//DFSArticul

/*
void print(ALGraph *graph){
	int i,j;
	printf("i\t");
	for(i=0;i<13;i++){
		printf("%4d",i);
	}
	putchar('\n');
	printf("data\t");
	for(i=0;i<13;i++){
		printf("%4d",graph->alist[i].data);
	}
	putchar('\n');
	printf("visit\t");
	for(i=0;i<13;i++){
		printf("%4d",visited[i]);
	}
	putchar('\n');
	printf("low\t");
	for(i=0;i<13;i++){
		printf("%4d",low[i]);
	}
	putchar('\n');

}
*/
