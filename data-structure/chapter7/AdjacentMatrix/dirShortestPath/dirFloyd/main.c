#include "AdjacentMatrix.h"
#include "Floyd.h"
#include<stdio.h>
int main(){
	MatrixGraph graph;
	int i,j,k;
	VRType des[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	createMG(&graph,DG);
	shortestPath_Floyd(&graph,des,path);
	for(i=0;i<graph.vertexNum;i++){
		for(j=0;j<graph.vertexNum;j++){
			if(des[i][j] != INFINITY)
			printf("%2d to %2d: cost:%4d\tpath:",i,j,des[i][j]);
			for(k=0;k<graph.vertexNum;k++){
				if(path[i][j][k] == 1){
					printf("%2d",k);
				}
			}
			putchar('\n');
		}
	}
}
