#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

void dijkstra(AlGraph G,PRTable T);
int main(){
     AlGraph G;
     PRTable T;
     int i;
     G = graph_create(DGW,7,12);
     T = prt_create(G->vexnum,0);
     dijkstra(G,T);
     for(i=0;i<G->vexnum;i++){
          printf("dist:%d\t",T->list[i].dist);
          prt_printThePath(G,T,T->startindex,i);
     }
     return 0;
}

void dijkstra(AlGraph G,PRTable T){
     PriorityQueue Q;
     HeapElemType e;
     int v,w;
     ArcNode p;

     Q = priq_init(2 * G->vexnum);
     e.v = T->startindex;
     e.weight = 0;
     priq_insert(e,Q,comp);
     while(!priq_isEmpty(Q)){
          e = priq_deleteMin(Q,comp);
          v = e.v;
          T->list[v].known = 1;
          for(p=G->vertices[v].firstarc;p;p=p->next){
               w = p->adjvex;
               if(T->list[w].known == 0 && T->list[v].dist + p->info->weight < T->list[w].dist){
                    T->list[w].dist = T->list[v].dist + p->info->weight;
                    T->list[w].path = v;
                    e.v = w;
                    e.weight = T->list[w].dist;
                    priq_insert(e,Q,comp);
               }
          }
     }
     priq_destroy(Q);
}
