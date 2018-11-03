#include "Polynomial.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Polynomial p1,p2,res;
	p1 = Create();
	p2 = Create();
	res = CreatePoly();
	AddPolynomial(p1,p2,res);
	print_polynomial(p1);
	print_polynomial(p2);
	print_polynomial(res);
	return 0;
}
