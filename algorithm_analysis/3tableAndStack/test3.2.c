#include "myerr.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintLots(List L,List P);
int main(){
	clock_t start,end;
	List L,P;
	Create(&L);
	Create(&P);

	start = clock();
	PrintLots(L,P);
	end = clock();
	printf("time:%f\n",(double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}

void PrintLots(List L,List P){
	Position q,p;
	int count = 1;
	q = L->next;
	p = P->next;
	while(q != NULL && p != NULL){
		if(count == Retrieve(p)){
			printf("%d,",Retrieve(q));
			p = p->next;
		}
		count++;
		q = q->next;
	}
}
