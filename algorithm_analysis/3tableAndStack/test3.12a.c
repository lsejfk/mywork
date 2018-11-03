#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List ReverseList(List L){
	Position p,s,q;
	p = L->next;
	s = p->next;

	p->next = NULL;		//cut down the list
	q = s;
	while(q){
		s = s->next;
		q->next = L->next;	//insert at the header
		L->next = q;

		q = s;
	}
	return L;
}

int main(){
	List L;
	Create(&L);
	link_list_print(L);
	ReverseList(L);
	link_list_print(L);

}
