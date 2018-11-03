#include "linklist.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

void init_link_list(struct LinkList *list){
	list->next = NULL;
}

void insert_into_list(struct LinkList *list,ElemType elem){
	struct LinkList *p;
	p = (struct LinkList *)malloc(sizeof(struct LinkList));
	if(p == NULL){
		err_sys("malloc failed");
	}

	p->elem = elem;		//copy data to elem
	//insert the node
	p->next = list->next;
	list->next = p;
}

void link_list_print(struct LinkList *list){
	struct LinkList *p;
	p = list->next;
	while(p != NULL){
		printf("%d,",p->elem);
		p = p->next;
	}
	printf("NULL\n");
}


//clean the list
List MakeEmpty(List L){
	PtrToNode p,q;
	p = L->next;
	while(p != NULL){
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

//check if the list is empty
int IsEmpty(List L){
	return L->next == NULL;
}

//return true if P is the last node,or return false
int IsLast(Position P,List L){
	Position p;
	p = L->next;
	if(p == NULL){
		return 0;
	}
	while(p->next != NULL){
		p = p->next;
	}
	return p->next == P;
}

//find out the position the element x in the list,if not exist ,return null
Position Find(ElemType x,List L){
	Position p;
	p = L->next;
	while(p != NULL && p->elem != x){
		p = p->next;
	}
	return p;
}

//delete element x from list
void Delete(ElemType x,List L){
	Position p,q;

	p = FindPrevious(x,L);
	if(p == NULL){
		return;
	}
	q = p->next;
	p->next = q->next;
	free(q);
}

//find the previous node of the node with value x
Position FindPrevious(ElemType x,List L){
	Position p;
	p = L;
	while(p->next != NULL && p->next->elem != x){
		p = p->next;
	}
	return p->next;
}

//insert a node after position p
void Insert(ElemType x,List L,Position P){
	PtrToNode q;
	q = (PtrToNode)malloc(sizeof(struct LinkList));
	if(q == NULL){
		err_sys("malloc failed");
	}
	q->elem = x;
	if(P == NULL){
		err_quit("P can't be NULL");
	}
	q->next = P->next;
	P->next = q;
}

//delete the list
void DeleteList(List L){
	Position P,tmp;
	P = L->next;
	L->next = NULL;
	while(P != NULL){
		tmp = P;
		P = P->next;
		free(tmp);
	}
}

//get the header of the list
Position Header(List L){
	return L;
}

//get the first element of the list
Position First(List L){
	return L->next;
}

//advance 
Position Advance(Position P){
	if(P == NULL){
		return NULL;
	}
	return P->next;
}

//get the element value with the Position 
ElemType Retrieve(Position P){
	if(P == NULL){
		return 0;
	}	
	return P->elem;
}

//create empty list
List CreateList(){
	List L;
	L = (PtrToNode)malloc(sizeof(struct LinkList));
	if(L == NULL){
		err_sys("malloc error");
	}
	L->next = NULL;
	return L;
}


//create the linklist
void Create(List *L){
	ElemType n;
	PtrToNode p,q;
	*L = (PtrToNode)malloc(sizeof(struct LinkList));
	if(*L == NULL){
		err_sys("malloc failed");
	}
	(*L)->next = NULL;
	q = *L;
	printf("Please input the elements seperated by space and end by EOF:\n");
	while(scanf("%d",&n) != EOF){
		p = (PtrToNode)malloc(sizeof(struct LinkList));
		if(p == NULL){
			err_sys("malloc failed");
		}
		p->elem = n;
		q->next = p;
		q = p;
		p->next = NULL;
	}
}



