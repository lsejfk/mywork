#include "adjlist.h"
#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>
//int isBG(AlGraph G,int vex,int arr[],int status,int visited[]);
int isBG(AlGraph G,int arr[],int visited[]);

int main(){
     AlGraph G;
     int i;
     int *arr,*visited;
     G = graph_create(DGW,4,4);
     arr = (int *)calloc(G->vexnum,sizeof(int));
     visited = (int *)calloc(G->vexnum,sizeof(int));
     if(visited == NULL){
          fprintf(stderr,"calloc failed\n");
          return 1;
     }
     for(i=0;i<G->vexnum;i++){
          arr[i] = 0;
          visited[i] = 0;
     }
     if(isBG(G,arr,visited)){
          printf("true\n");
     }else{
          printf("false\n");
     }
     return 0;
}

/*
int isBG(AlGraph G){
     DisjointSet S;
     DSetType A,B,t,m;
     int i,j;
     ArcNode p;
     A = 0;
     B = G->vertices[A].firstarc->adjvex;
     for(i=0;i<G->vexnum;i++){
          t = dis_find(i,S);
          if(A == t){
               for(p=G->vertices[i].firstarc;p;p=p->next){
                    j = p->adjvex;
                    m = dis_find(j,S);
                    if(A == m){
                         return 0;
                    }else if(B != m){
                         dis_setUnion(S,B,j);
                    }
               }
          }else if(B == t){
               for(p=G->vertices[i].firstarc;p;p=p->next){
                    j = p->adjvex;
                    m = dis_find(j,S);
                    if(B == m){
                         return 0;
                    }else if(A != m){
                         dis_setUnion(S,A,j);
                    }
               }
          }else{
               dis_setUnion(S,A,t);
               for(p=G->vertices[i].firstarc;p;p=p->next){
                    j = p->adjvex;
                    m = dis_find(j,S);
                    if(A == m){
                         return 0;
                    }else if(B != m){
                         dis_setUnion(S,B,j);
                    }
               }
          }
     }
     return 1;
}

*/
/*

int isBG(AlGraph G,int vex,int arr[],int status,int visited[]){
     ArcNode p;
     if(arr[vex] == status){
          return 1;
     }else if(arr[vex] == 0){
          arr[vex] = status;
     }else{
          return 0;
     }
     visited[vex] = 1;
     for(p=G->vertices[vex].firstarc;p;p=p->next){
          if(visited[p->adjvex] == 0 && isBG(G,p->adjvex,arr,(-1)*status,visited)){
               return 1;
          }
     }
     return 0;
}
*/
int isBG(AlGraph G,int arr[],int visited[]){
     Stack S;
     int i;
     ArcNode p;
     S = arr_createStack(G->vexnum);
     arr_push(0,S);
     arr[0] = 1;
     while(!arr_isEmpty(S)){
          i = arr_topAndPop(S);
          visited[i] = 1;
          for(p=G->vertices[i].firstarc;p;p=p->next){
               if(visited[p->adjvex] == 0){
                    arr_push(p->adjvex,S);
               }
               if(arr[p->adjvex] == 0){
                    arr[p->adjvex] = arr[i] * (-1);
               }else if(arr[p->adjvex] == arr[i]){
                    return 0;
               }
          }
     }
     return 1;
}
