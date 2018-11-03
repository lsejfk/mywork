#include "AdjacentMatrix.h"
	typedef struct {
		int serial;
		VRType lowestW;			//the lowest weight of arcs
	}Edge[MAX_VERTEX_NUM];

//input information about arc
void inputInfo(){

}


//create undirected graph in adjacent matrix form
void createMG(MatrixGraph *graph,GraphKind kind){
	int i,j,info,l,r,w;	
	scanf("%d%d%d",&graph->vertexNum,&graph->arcNum,&info);		//input the number of vertexs and arcs,
									//0 for info means no information for arcs
	for(i=0;i<graph->vertexNum;i++){				//input the vertex vector
		scanf("%s",graph->vex[i]);
	}
	//initialize the adjacent matrix
	for(i=0;i<graph->vertexNum;i++){
		for(j=0;j<graph->vertexNum;j++){
			graph->arcs[i][j].adj = INFINITY;
			graph->arcs[i][j].info = NULL;
		}
	}

	for(i=0;i<graph->arcNum;i++){
		scanf("%d%d%d",&l,&r,&w);				//input the serial number of two vertexs and
										//the arc weight between the two vertexs 
		graph->arcs[l][r].adj = w;
		if(kind == UDG){
			graph->arcs[r][l].adj = w;
		}
	}
	if(info){							//input the information if needed
		inputInfo();
	}
	graph->kind = kind;						//the type of graph
}
//find the lowest weight
int minWeight(Edge closedge,int num){
	int i,k;
	VRType w;
	w = INFINITY;
	for(i=0;i<num;i++){
		if(closedge[i].lowestW != INFINITY && closedge[i].lowestW != 0){
			if(w == INFINITY){
				k = i;
				w = closedge[i].lowestW;
			}else if(closedge[i].lowestW < w){
				k = i;
				w = closedge[i].lowestW;
			}
		}
	}
	return k;
}


int locateVex(VertexType vex,MatrixGraph *graph){
	int i;
	for(i=0;i<graph->vertexNum;i++){
		if(strcmp(vex,graph->vex[i]) == 0){
			return i;
		}
	}

	return -1;
}
//build a minimum cost spanning tree by prim algorithm
void miniSpanTree_prim(MatrixGraph *graph,VertexType vex){
	int k,i,j;
	Edge closedge;
	k = locateVex(vex,graph);				//get the location of vertex in the array
	for(i=0;i<graph->vertexNum;i++){			//initialize the closedge array
		if(i != k){
			closedge[i].serial = k;
			closedge[i].lowestW = graph->arcs[k][i].adj;
		}
	}
	closedge[k].lowestW = 0;				//start at k

	for(i=0;i<graph->vertexNum-1;i++){			//choose the n-1 vertexs
		k = minWeight(closedge,graph->vertexNum);	//find the lowest weight
		printf("(%s,%s)\n",graph->vex[closedge[k].serial],graph->vex[k]);	//output the new way
		closedge[k].lowestW = 0;			//push the kth vertex into the set U
		for(j=0;j<graph->vertexNum;j++){		//adjust the lowest weight
			if(graph->arcs[k][j].adj != INFINITY&& 
				closedge[j].lowestW != INFINITY && 
					graph->arcs[k][j].adj < closedge[j].lowestW){
				closedge[j].lowestW = graph->arcs[k][j].adj;
				closedge[j].serial = k;
			}else if(closedge[j].lowestW == INFINITY){
				closedge[j].lowestW = graph->arcs[k][j].adj;
				closedge[j].serial = k;
			}
		}
	}
}
