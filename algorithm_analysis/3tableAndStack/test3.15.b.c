#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	List L;
	Position p,pre;
	Create(&L);
	link_list_print(L);
	p = Find(99,L);
	pre = FindPrevious(p->elem,L);
	pre->next = p->next;
	p->next = L->next;
	L->next = p;
	link_list_print(L);
}
