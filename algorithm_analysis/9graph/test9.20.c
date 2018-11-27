#include <stdio.h>
#include <stdlib.h>
#include "adjlist.h"

void prim(AlGraph G,PRTable T){
     PriorityQueue H;
     HeapElemType e;
     int i,j;
     H = priq_init(G->vexnum * G->vexnum);
     //enqueue
     e = init();    //initialize 
     priq_insert(e,H);
     while(!priq_isEmpty(H)){
          do{
               e = priq_deleteMax(H);
          }while(!priq_isEmpty(H) && T->list[e.index].known == 1);
          if(T->list[e.index].known == 1){
               break;
          }
          i = e.index;
          for(p=G->vertices[i].firstarc;p;p=p->next){
               j = p->adjvex;
               if(T->list[j].known == 0){
                    if(p->info->weight > T->list[j].dist){
                         T->list[j].dist = p->info->weight;
                         T->list[j].path = i;
                         e = init();
                         priq_insert(e,H);
                    }
               }
          }
     }
     priq_destroy(H);
}
/*
 *e{
     int v;
     int u;
     int weight;
     }
 *
 *
 */

void kruskal(AlGraph G){
     DisjointSet S;
     DSetType uset,vset;
     PriorityQueue H;
     HeapElemType e;
     int count;

     dis_init(S);
     H = priq_init(G->vexnum * G->vexnum);
     buildHeap(G,H);     //assume one edge for one element
     count = 0;
     while(count < G->vexnum-1){
          e = priq_deleteMax(H);
          uset = dis_find(e.u,S);
          vset = dis_find(e.v,S);
          if(uset != vset){
               dis_setUnion(S,uset,vset);
               printf("(%d,%d,%d),",e.u,e.v,e.weight);
               count++;
          }
     }
     priq_destroy(H);

}
