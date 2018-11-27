#include "adjlist.h"
#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>
void shortestpath(AlGraph G,PRTable T);

int main(){
     AlGraph G;
     PRTable T;
     int i;
     G = graph_create(DG,7,12);
     T = prt_create(G->vexnum,0);
     shortestpath(G,T);
     for(i=0;i<G->vexnum;i++){
          printf("dist:%d\t",T->list[i].dist);
          prt_printThePath(G,T,0,i);
     }
     return 0;
}

void shortestpath(AlGraph G,PRTable T){
     ArrQueue Q;
     ArcNode p;
     int v,w;
     Q = arrque_createQueue(G->vexnum);
     arrque_enqueue(T->startindex,Q);
     while(!arrque_isEmpty(Q)){
          v = arrque_frontAndDequeue(Q);
          for(p=G->vertices[v].firstarc;p;p=p->next){
               w = p->adjvex;
               if(T->list[w].dist == INFINITE){
                    T->list[w].dist = T->list[v].dist + 1;
                    T->list[w].path = v;
                    arrque_enqueue(w,Q);
               }
          }
     }
     arrque_disposeQueue(Q);
}
