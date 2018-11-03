#include "Polynomial.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Polynomial p1,p2,p,res;
	PtrToPolyNode q1,q2,q,n,s;
	p1 = Create();
	p2 = Create();
	p = CreatePoly();
	res = CreatePoly();

	q = p;
	for(q1=p1->next;q1;q1=q1->next){
		for(q2=p2->next;q2;q2=q2->next){
			n = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
			if(n == NULL){
				err_sys("malloc error");
			}
			n->Coefficient = q1->Coefficient * q2->Coefficient;
			n->Exponent = q1->Exponent + q2->Exponent;
			n->next = NULL;
			q->next = n;
			q = n;
		}
	}
	qsort(
}
