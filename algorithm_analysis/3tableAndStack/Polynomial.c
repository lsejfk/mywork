#include "Polynomial.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 

Polynomial CreatePoly(){
	PtrToPolyNode p;
	p = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
	if(p == NULL){
		err_sys("malloc failed");
	}
	p->next = NULL;
	return p;
}

//create polynomial with standard input
Polynomial Create(){
	int coe,exp;
	PtrToPolyNode p,header,q;

	header = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
	if(header == NULL){
		err_sys("malloc failed");
	}
	q = header;
	header->next = NULL;

	printf("Please input the groups of coefficients and exponents,end by EOF\n");
	while(scanf("%d%d",&coe,&exp) != EOF){
		p = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
		if(p == NULL){
			err_sys("malloc failed");
		}
		p->Coefficient = coe;
		p->Exponent = exp;
		p->next = NULL;
		q->next = p;
		q = p;
	}//while
	return header;
}

int isInArr(int arr[],int n,int elem){
	int i;
	for(i=0;i<n;i++){
		if(arr[i] == elem){
			return 1;
		}
	}
	return 0;
}

void AddPolynomial(const Polynomial Poly1,const Polynomial Poly2,Polynomial PolySum){
	PtrToPolyNode p1,p2,ps,q;
	int i,arr[MAXSIZE],flag;
	ps = PolySum;
	i = 0;
	for(p1=Poly1->next;p1;p1=p1->next){
		flag = 0;	//suppose p1 is alone
		for(p2=Poly2->next;p2;p2=p2->next){
			if(p2->Exponent == p1->Exponent){
				q = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
				if(q == NULL){
					err_sys("malloc failed");
				}
				q->Coefficient = p1->Coefficient + p2->Coefficient;
				q->Exponent = p1->Exponent;
				q->next = NULL;
				ps->next = q;
				ps = q;
				arr[i++] = p1->Exponent;	//record term with the same exponent in p1 and p2
				flag = 1;			//not alone 
			}//if
		}//for p2
		if(!flag){			//the alone item
			q = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
			if(q == NULL){
				err_sys("malloc failed");
			}
			q->Coefficient = p1->Coefficient;
			q->Exponent = p1->Exponent;
			q->next = NULL;
			ps->next = q;
			ps = q;
		}//if flag
	}//for p1

	for(p2=Poly2->next;p2;p2=p2->next){
		if(!isInArr(arr,i,p2->Exponent)){
			q = (PtrToPolyNode)malloc(sizeof(struct PolyNode));
			if(q == NULL){
				err_sys("malloc failed");
			}
			q->Coefficient = p2->Coefficient;
			q->Exponent = p2->Exponent;
			q->next = NULL;
			ps->next = q;
			ps = q;
		}//if
	}//for
}

void print_polynomial(Polynomial Poly){
	PtrToPolyNode p;
	for(p=Poly->next;p;p=p->next){
		printf("%dX^%d + ",p->Coefficient,p->Exponent);
	}
	printf("0\n");
}


//the function suppose the number of items of p2 less than p1
Polynomial MultiPoly(Polynomial p1,Polynomial p2){
	Polynomial p,res;
	PtrToPolyNode q1,q2,q,s;
	int n,c;
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
	return res;
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
