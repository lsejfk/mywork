#include "AdjacentMatrix.h"

//find the shortest path
void shortestPath_Floyd(MatrixGraph *graph,VRType des[][MAX_VERTEX_NUM],int path[][MAX_VERTEX_NUM][MAX_VERTEX_NUM]){
	int v,w,u,i;
	//initialize
	for(v=0;v<graph->vertexNum;v++){
		for(w=0;w<graph->vertexNum;w++){
			des[v][w] = graph->arcs[v][w].adj;	//the minimum cost from v to w
			for(u=0;u<graph->vertexNum;u++){
				path[v][w][u] = 0;		//vertex u is not in the path from v to w
			}
			if(des[v][w] < INFINITY){		//there is a direct way from v to w
				path[v][w][v] = 1;
				path[v][w][w] = 1;
			}
		}
	}//for v
	for(v=0;v<graph->vertexNum;v++){
		for(u=0;u<graph->vertexNum;u++){
			for(w=0;w<graph->vertexNum;w++){
				if(des[v][u] != INFINITY && des[u][w] != INFINITY
					&& des[v][u] + des[u][w] < des[v][w]){	//a shorter path from v to w through u
					des[v][w] = des[v][u] + des[u][w];
					for(i=0;i<graph->vertexNum;i++){
						path[v][w][i] = (path[v][u][i] || path[u][w][i]);
					}//for i
				}//if
			}//for w
		}//for u
	}//for v

}
