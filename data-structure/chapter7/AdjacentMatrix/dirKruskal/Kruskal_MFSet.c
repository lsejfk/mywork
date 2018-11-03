#include "MFSet.h"
#include "Kruskal_MFSet.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct Vertex{
	char vexname[10];		//the name of vertex
	int parent;			//the parent of the vertex
}Vertex;
//define the struct 
struct MFSetADT {
	Vertex *vex;			//the vertex set
	int num;			//the number of vertexs
};

void initMFSet(MFSet s){
	Vertex *p;
	int vexnum,i;
	scanf("%d",&vexnum);
	p = (Vertex *)malloc(sizeof(Vertex) * vexnum);	//create the array of vertex
	assert(p != NULL);
	for(i=0;i<vexnum;i++){
		scanf("%s",p[i].vexname);
		p[i].parent = -1;
	}
	s->vex = p;
	s->num = vexnum;
}

//input the arcs
int inputArcs(Arc **arc){
	int arcnum,i,j,it,jt,tmpi,tmpj;
	VRCost tmpw,w;
	Arc *p;
	scanf("%d",&arcnum);					//input the number of arcs
	p = (Arc *)malloc(sizeof(Arc) * arcnum);
	assert(p != NULL);
	for(i=0;i<arcnum;i++){
		scanf("%d%d%d",&it,&jt,&w);			//input the information of arcs
		p[i].i = it;
		p[i].j = jt;
		p[i].weight = w;
		for(j=i;j>0;j--){		//sort by weight
			if(w < p[j-1].weight){
				tmpi = p[j-1].i;
				tmpj = p[j-1].j;
				tmpw = p[j-1].weight;
				p[j-1].i = p[j].i;
				p[j-1].j = p[j].j;
				p[j-1].weight = p[j].weight;
				p[j].i = tmpi;
				p[j].j = tmpj;
				p[j].weight = tmpw;
			}
		}
	}
	*arc = p;
	return arcnum;
}
//find the subset to which s belongs
int find(MFSet s,int elem){
	int i;
	if(elem < 0 || elem >= s->num){
		return -1;			//elem invalid
	}
	if(s->vex[elem].parent < 0){		//the root
		return elem;
	}
	for(i=s->vex[elem].parent;s->vex[i].parent>0;i=s->vex[i].parent)
		;				//find the root of the tree
	return i;
}

//merge two subset into one set
void merge(MFSet s,int i,int j){
	if(i < 0 || i >= s->num || j < 0 || j >= s->num){	//i or j invalid
		fprintf(stderr,"error:merge:i or j invalid\n");
		return;
	}
	if(s->vex[i].parent > s->vex[j].parent){		//the number of element in set i is lower than set j
		s->vex[j].parent += s->vex[i].parent;		//merge set i into set j
		s->vex[i].parent = j;
	}else{
		s->vex[i].parent += s->vex[j].parent;
		s->vex[j].parent = i;
	}
}

int selectMinArc(int visited[],Arc *arc,MFSet s,int arcnum){
	int i,it,jt;
	for(i=0;i<arcnum;i++){
		if(!visited[i]){				//if un-visited
			visited[i] = 1;
			it = find(s,arc[i].i);			//find the serial of set to which the vertex belongs
			jt = find(s,arc[i].j);
			if(it != jt){				//the two vertices are distributed in different sets
				return i;
			}
		}
	}
	return -1;						//there is a error
}

//build the minimum Cost Spanning Tree
void miniSpanTree_kruskal(MFSet s,Arc *arc,int arcnum){
	int k,i,it,jt;
	int *visited;
	visited = (int *)malloc(sizeof(int) * arcnum);
	assert(visited != NULL);
	for(i=0;i<arcnum;i++){					//initialize the visited
		visited[i] = 0;
	}
	for(i=0;i<s->num-1;i++){				//find the n-1 arcs
		k = selectMinArc(visited,arc,s,arcnum);		//select the minimum un-visited arc
		it = find(s,arc[k].i);				//find the serial of set to which the vertex belongs
		jt = find(s,arc[k].j);
		merge(s,it,jt);					//merge the two set
		printf("(%s,%s)\n",s->vex[arc[k].i].vexname,s->vex[arc[k].j].vexname);
	}
}
