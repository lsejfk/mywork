#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityqueue.h"
static void prim(AlGraph G,PRTable T);

int main(){
     AlGraph G;
     PRTable T;
     G = graph_create(UDGW,7,12);
     T = prt_create(G->vexnum,0);
     prim(G,T);
     prt_printtab(T);
     return 0;
}

static void prim(AlGraph G,PRTable T){
     PriorityQueue H;
     int v,w;
     HeapElemType e,m;
     ArcNode p;
     H = priq_init(G->vexnum * G->vexnum);
     e.dist = T->list[T->startindex].dist;
     e.index = T->startindex;
     priq_insert(e,H,comp);
     while(!priq_isEmpty(H)){
          do{
               m = priq_deleteMin(H,comp);
               v = m.index;
          }while(!priq_isEmpty(H) && T->list[v].known == 1);
          if(priq_isEmpty(H) && T->list[v].known == 1){
               break;
          }
          T->list[v].known = 1;
          for(p=G->vertices[v].firstarc;p;p=p->next){
               w = p->adjvex;
               if(T->list[w].known == 0){
                    if(p->info->weight < T->list[w].dist){
                         T->list[w].dist = p->info->weight;
                         e.dist = p->info->weight;
                         e.index = w;
                         priq_insert(e,H,comp);
                         T->list[w].path = v;
                    }//if
               }//if
          }//for p
     }//while
}
