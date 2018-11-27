#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityqueue.h"
#include "disjointset.h"
static void kruskal(AlGraph G,PRTable T);
static void readFromGraph(PriorityQueue H,AlGraph G,PRTable T);

int main(){
     AlGraph G;
     PRTable T;
     G = graph_create(UDGW,7,12);
     T = prt_create(G->vexnum,0);
     kruskal(G,T);
     return 0;
}

static void kruskal(AlGraph G,PRTable T){
     PriorityQueue H;
     int acceptedEdge;
     DisjointSet S;
     HeapElemType edge;
     DSetType ve,ue;

     H = priq_init(G->arcnum);
     readFromGraph(H,G,T);
     H = priq_buildHeap(H,comp);
     dis_init(S);
     acceptedEdge = 0;
     while(acceptedEdge < G->vexnum - 1){
          edge = priq_deleteMin(H,comp);
          ve = dis_find(edge->v,S);
          ue = dis_find(edge->u,S);
          if(ve != ue){
               /*
               if(edge->weight < T->list[edge->v].dist){
                    T->list[edge->v].dist = edge->weight;
                    T->list[edge->v].path = edge->u;
               }
               if(edge->weight < T->list[edge->u].dist){
                    T->list[edge->u].dist = edge->weight;
                    T->list[edge->u].path = edge->v;
               }
               */
               printf("(v%d,v%d,%d),",edge->v+1,edge->u+1,edge->weight);
               free(edge);
               dis_setUnion(S,ve,ue);
               acceptedEdge++;
          }
     }
     printf("\n");
}

static void readFromGraph(PriorityQueue H,AlGraph G,PRTable T){
     ArcNode p;
     HeapElemType q;
     int i,j;
     for(i=0,j=1;i<G->vexnum;i++){
          for(p=G->vertices[i].firstarc;p;p=p->next){
               if(T->list[p->adjvex].known == 0){
                    if(j > H->capacity){
                         return;
                    }
                    /*
                    q = (HeapElemType)malloc(sizeof(struct heap_tag));
                    if(q == NULL){
                         fprintf(stderr,"malloc failed\n");
                         exit(1);
                    }
                    q->v = i;
                    q->u = p->adjvex;
                    q->weight = p->info->weight;
                    priq_insert(q,H,comp);
                    */
                    H->elem[j]->v = i;
                    H->elem[j]->u = p->adjvex;
                    H->elem[j]->weight = p->info->weight;
                    j++;
               }
          }
          T->list[i].known = 1;
     }
     H->size = j - 1;
}
