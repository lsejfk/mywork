#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>

struct node{
     int num;
     int low;
     int visited;
     int parent;
};
static int count = 0;
static struct node list[11];

void findArt(AlGraph G,int v){
     int w;
    // static int n = 0;
     ArcNode p;
     list[v].low = list[v].num = ++count;
     list[v].visited = 1;
     for(p=G->vertices[v].firstarc;p;p=p->next){
          w = p->adjvex;
          if(list[w].visited == 0){     //forward edge
               list[w].parent = v;
               //if(v == start){
               //    n++;
               //}
               findArt(G,w);
               if(list[w].low >= list[v].num){
                    printf("%s,",G->vertices[v].data->name);
               }
               //if(n > 1){
               //     printf("%s,",G->vertices[v].data->name);
               //}
               if(list[w].low < list[v].low){
                    list[v].low = list[w].low;
               }
          }else if(list[v].parent != w){     //back edge
               if(list[w].num < list[v].low){
                    list[v].low = list[w].num;
               }
          }
     }//for p
}

int main(){
     AlGraph G;
     ArcNode p;
     int i,v;

     G = graph_create(UDG,12,14);
     p = G->vertices[0].firstarc;
     v = p->adjvex;
     findArt(G,v);
     if(count < G->vexnum){
          printf("%s,",G->vertices[v].data->name);
          while(p->next){
               p = p->next;
               if(!list[p->adjvex].visited){
                    findArt(G,p->adjvex);
               }
          }
     }
     printf("\n");
     printf("vertice\t\tnum\t\tlow\t\tparent\t\t\n");
     for(i=0;i<G->vexnum;i++){
          printf("%s\t\t%d\t\t%d\t\t%s\t\t\n",G->vertices[i].data->name,list[i].num,list[i].low,G->vertices[list[i].parent].data->name);
     }
     return 0;
}
