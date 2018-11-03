#include "myerr.h"
#include "Polynomial.h"
#include <stdio.h>
#include <stdlib.h>
Polynomial SqPoly(Polynomial X);
Polynomial ExPolynomial(Polynomial F,long p);

int main(){
	long p;
	Polynomial F;
	F = Create();
	scanf("%ld",&p);
	print_polynomial(ExPolynomial(F,p));
	return 0;
}

int is_even(int p){
	return p % 2 == 0;
}

Polynomial ExPolynomial(Polynomial F,long p){
	if(p == 0){
		return 0;
	}
	if(p == 1){
		return F;
	}
	if(is_even(p)){
		return ExPolynomial(SqPoly(F),p/2);
	}else{
		return MultiPoly(ExPolynomial(SqPoly(F),p/2),F);
	}
}

Polynomial SqPoly(Polynomial X){
	PtrToPolyNode q,s,m,n,res;
	res = CreatePoly();
	for(q=X->next;q;q=q->next){
		for(s=q;s;s=s->next){
			m = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
			if(m == NULL){
				err_sys("malloc failed");
			}
			if(q == s){
				m->Coefficient = q->Coefficient * q->Coefficient;
			}else{
				m->Coefficient = 2 * q->Coefficient * s->Coefficient;
			}
			m->Exponent = q->Exponent + s->Exponent;
			m->next = NULL;
			for(n=res;n->next && m->Exponent > n->next->Exponent;n=n->next)
				;
			if(n->next == NULL){
				n->next = m;
			}else if(m->Exponent == n->next->Exponent){
				n->next->Coefficient += m->Coefficient;
			}else{
				m->next = n->next;
				n->next = m;
			}
		}//for s
	}//for q
	return res;
}
