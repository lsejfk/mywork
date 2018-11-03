#include "Polynomial.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Polynomial p1,p2,p,res;
	PtrToPolyNode q1,q2,q,s;
	int n,c;

	p1 = Create();
	p2 = Create();
	p = CreatePoly();
	res = CreatePoly();

	for(q1=p1->next;q1;q1=q1->next){
		//suppose the number of items of p2 less than p1
		for(q2=p2->next;q2;q2=q2->next){
			n = q1->Exponent + q2->Exponent;
			c = q1->Coefficient * q2->Coefficient;
			for(q=res;q->next && n > q->next->Exponent;q=q->next)
				;
			if(q->next == NULL){
				s = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
				if(s == NULL){
					err_sys("malloc error");
				}
				s->Exponent = n;
				s->Coefficient = c;
				s->next = NULL;
				q->next = s;
			}else if(q->next->Exponent == n){
				q->next->Coefficient += c;
			}else{
				s = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
				if(s == NULL){
					err_sys("malloc error");
				}
				s->Exponent = n;
				s->Coefficient = c;
				s->next = q->next;
				q->next = s;
			}//if
		}//for q2
	}//for q1
	print_polynomial(res);
}
