#include "disjointset.h"
#include <stdio.h>
#include <stdlib.h>

void dis_init(DisjointSet S){
     int i;
     for(i=DISJOINT_NUM_SET;i>=0;i--){
          S[i] = -1;
     }
}

void dis_setUnion(DisjointSet S,DSetType root1,DSetType root2){
     if(S[root1] < S[root2]){
          S[root1] += S[root2];
          S[root2] = root1;
     }else if(S[root2] < S[root1]){
          S[root2] += S[root1];
          S[root1] = root2;
     }
}

DSetType dis_find(DisElemType x,DisjointSet S){
     if(S[x] <= 0){
          return x;
     }else{
          return S[x] = dis_find(S[x],S);
     }
}

