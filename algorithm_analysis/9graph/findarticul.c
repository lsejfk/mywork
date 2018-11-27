#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_VEX 100
static int visited[MAX_NUM_VEX];
static int low[MAX_NUM_VEX];
static int num[MAX_NUM_VEX];
static int parent[MAX_NUM_VEX];
static int count;
static int root;
static void findArt(AlGraph G,int vertex);

int main(){
     AlGraph G;
     G = graph_create(UDG,13,17);
     root = 0;
     findArt(G,root);
     /*
     if(count < G->vexnum){   //there are more than one child
          printf("%s,",G->vertices[0].data->name);
          p = p->next;
          while(p){
               findArt(G,p->adjvex);
               p = p->next;
          }
     }
     */
     return 0;
}

static void findArt(AlGraph G,int vertex){
     int w;
     ArcNode p;
     low[vertex] = num[vertex] = ++count;
     visited[vertex] = 1;
     for(p=G->vertices[vertex].firstarc;p;p=p->next){
          w = p->adjvex;
          if(!visited[w]){
               if(vertex == root && p != G->vertices[root].firstarc){
                    printf("%s,",G->vertices[root].data->name);
               }
               parent[w] = vertex;
               findArt(G,w);
               if(low[w] >= num[vertex]){
                    printf("%s,",G->vertices[vertex].data->name);
               }
               if(low[w] < low[vertex]){
                    low[vertex] = low[w];
               }
          }else{
               if(parent[vertex] != w){
                    if(num[w] < low[vertex]){
                         low[vertex] = num[w];
                    }
               }
          }
     }
}
