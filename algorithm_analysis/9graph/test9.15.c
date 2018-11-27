#include "adjlist.h"
#include "priorityqueue.h"
#include "disjointset.h"
#include <stdio.h>
#include <stdlib.h>
void kruskal(AlGraph G);
void prim(AlGraph G,PRTable T);

int main(){
     AlGraph G;
     PRTable T;

     G = graph_create(UDGW,10,19);
     T = prt_create(G->vexnum,0);
     printf("with prim algorithm:\n");
     prim(G,T);
     prt_printtab(G,T);

     printf("\nkruskal algorithm:\n");
     kruskal(G);
     return 0;
}


void prim(AlGraph G,PRTable T){
     PriorityQueue H;
     HeapElemType e;
     int i,j;
     ArcNode p;
     H = priq_init(G->vexnum * G->vexnum);
     e.v = T->startindex;
     e.weight = T->list[T->startindex].dist;
     e.u = T->startindex;

     priq_insert(e,H,comp);
     T->list[T->startindex].known = 1;
     while(!priq_isEmpty(H)){
          do{
               e = priq_deleteMin(H,comp);
               i = e.v;
          }while(!priq_isEmpty(H) && T->list[i].known == 1);

          T->list[i].known = 1;
          for(p=G->vertices[i].firstarc;p;p=p->next){
               j = p->adjvex;
               if(T->list[j].known == 0){
                    if(p->info->weight < T->list[j].dist){
                         e.v = j;
                         e.weight = p->info->weight;
                         priq_insert(e,H,comp);
                         T->list[j].dist = p->info->weight;
                         T->list[j].path = i;
                    }
               }
          }//for
     }//while
     priq_destroy(H);
}

void kruskal(AlGraph G){
     PriorityQueue H;
     DisjointSet S;
     HeapElemType e;
     DSetType type1,type2;
//     DisElemType e;
     int i,count;
     ArcNode p;
     dis_init(S);

     H = priq_init(G->vexnum * G->vexnum);
     for(i=0;i<G->vexnum;i++){
          for(p=G->vertices[i].firstarc;p;p=p->next){
               e.v = i;
               e.u = p->adjvex;
               e.weight = p->info->weight;
               priq_insert(e,H,comp);
          }
     }
     count = 0;
     while(count < G->vexnum-1){
          e = priq_deleteMin(H,comp);
          type1 = dis_find(e.v,S);
          type2 = dis_find(e.u,S);
          if(type1 != type2){
               dis_setUnion(S,type1,type2);
               count++;
               printf("(%s,%s,%d),",G->vertices[e.v].data->name,G->vertices[e.u].data->name,e.weight);
          }
     }
     

     priq_destroy(H);
}
