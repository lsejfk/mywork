#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef int ElemType;

struct LinkList{
	ElemType elem;
	struct LinkList *next;
};

typedef struct LinkList *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L);
Position Find(ElemType x,List L);
void Delete(ElemType x,List L);
Position FindPrevious(ElemType x,List L);
void Insert(ElemType x,List L,Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElemType Retrieve(Position P);
void Create(List *L);
List CreateList();


void init_link_list(struct LinkList *);
void insert_into_list(struct LinkList *,ElemType elem);
void link_list_print(struct LinkList *);

#endif
