#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
struct PolyNode{
	int Coefficient;
	int Exponent;
	struct PolyNode *next;
};

typedef struct PolyNode *PtrToPolyNode;
typedef PtrToPolyNode Polynomial;



void print_polynomial(Polynomial Poly);
void AddPolynomial(const Polynomial Poly1,const Polynomial Poly2,Polynomial PolySum);
Polynomial Create();
Polynomial CreatePoly();
Polynomial MultiPoly(Polynomial p1,Polynomial p2);
int is_even(long p);
Polynomial ExPolynomial(Polynomial F,long p);
Polynomial SqPoly(Polynomial X);
#endif
