#include "AdjacentMatrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//find the shortest path in way of Dijkstra Algorithm
void shortestPath_Dij(MatrixGraph *graph,int v0,VRType dij[],int path[][MAX_VERTEX_NUM]){
	VRType min;
	int *final,i,j,k,m;
	final = (int *)malloc(sizeof(int) * graph->vertexNum);		//an array of whether the vertex has been added into 
										//shortest path queue
	assert(final != NULL);
	
	for(i=0;i<graph->vertexNum;i++){					//initialize dij and final
		final[i] = 0;
		dij[i] = graph->arcs[0][i].adj;
		if(dij[i] < INFINITY){
			path[i][v0] = 1;
			path[i][i] = 1;
		}
	}
	final[v0] = 1;								//start from v0
	for(i=1;i<graph->vertexNum;i++){
		min = INFINITY;
		for(j=0;j<graph->vertexNum;j++){				//find the shortest path from v0 to other vertexs
			if(final[j] == 0 && dij[j] < min){
				min = dij[j];
				k = j;
			}
		}
		final[k] = 1;							//add k into shortest path
		//check which line is the shortest path :v0 to v directly or v0 to vk to v
		for(j=0;j<graph->vertexNum;j++){
			if(final[j] == 0 && min != INFINITY && graph->arcs[k][j].adj != INFINITY
				&& min + graph->arcs[k][j].adj < dij[j]){
				dij[j] = min + graph->arcs[k][j].adj;
				for(m=0;m<graph->vertexNum;m++){		//copy path[k] to path[j]
					path[j][m] = path[k][m];
				}
				path[j][j] = 1;
			}//if
		}//for
	}//for
}
