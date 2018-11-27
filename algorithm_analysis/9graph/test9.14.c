#include "adjlist.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
int findmax(PRTable T);
void findaugpath(AlGraph G,PRTable T,int end);
void printaugpath(AlGraph G,PRTable T,int start,int end);

int main(){
     AlGraph G;
     PRTable T;
     G = graph_create(DGW,6,8);
     T = prt_create(G->vexnum,0);
     findaugpath(G,T,5);
     printaugpath(G,T,0,5);
     return 0;
}

void findaugpath(AlGraph G,PRTable T,int end){
     int i,j;
     ArcNode p;

     for(;;){
          i = findmax(T);
          if(i < 0){
               return;
          }
          T->list[i].known = 1;
          for(p=G->vertices[i].firstarc;p;p=p->next){
               j = p->adjvex;
               if(T->list[j].known == 0){
                    if(p->info->weight > T->list[j].dist){
                         T->list[j].dist = p->info->weight;
                         T->list[j].path = i;
                    }
                    if(j == end){
                         return;
                    }
               }//if T
          }//for
     }//for
}

int findmax(PRTable T){
     int i,j;
     int max;
     max = INFINITE;
     j = -1;
     for(i=0;i<T->size;i++){
         if(T->list[i].known == 0 && T->list[i].dist > max){
               max = T->list[i].dist;
               j = i;
         }
     }
     return j;
}

void printaugpath(AlGraph G,PRTable T,int start,int end){
     int cur;
     int liu;
     cur = end;
     liu = 2147483647;
     while(cur != start){
          printf("%s,",G->vertices[cur].data->name);
          if(T->list[cur].dist < liu){
               liu = T->list[cur].dist;
          }
          cur = T->list[cur].path;
     }
     printf("%s :%d\n",G->vertices[cur].data->name,liu);
}
