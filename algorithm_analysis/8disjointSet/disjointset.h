#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#define DISJOINT_NUM_SET 1000
typedef int DisjointSet[DISJOINT_NUM_SET + 1];
typedef int DSetType;
typedef int DisElemType;

void dis_init(DisjointSet S);
void dis_setUnion(DisjointSet S,DSetType root1,DSetType root2);
DSetType dis_find(DisElemType x,Disjointset S);
#endif
