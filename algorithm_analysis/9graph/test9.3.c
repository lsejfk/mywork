#include "adjlist.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
void toposort(AlGraph G);

int main(){
     AlGraph G;
     G = graph_create(DGW,11,21);
     toposort(G);
     return 0;
}    

void toposort(AlGraph G){
     Stack S;
     int *indegree;
     int i,j;
     ArcNode p;
     S = arr_createStack(G->vexnum);
     indegree = (int *)calloc(G->vexnum,sizeof(int));
     if(indegree == NULL){
          fprintf(stderr,"toposort:calloc failed\n");
     }
     for(i=0;i<G->vexnum;i++){
          indegree[i] = 0;
     }
     for(i=0;i<G->vexnum;i++){
          for(p=G->vertices[i].firstarc;p;p=p->next){
               j = p->adjvex;
               indegree[j]++;
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
     printf("\n");
}
