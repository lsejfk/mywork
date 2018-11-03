#include "linklist.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	List L1,L2;
	Position p1,p2,p;
	List res = CreateList();
	Create(&L1);
	Create(&L2);
	p = Header(res);
	p1 = First(L1);
	p2 = First(L2);

	while(p1 && p2){
		if(Retrieve(p1) < Retrieve(p2)){
			Insert(Retrieve(p1),res,p);
			p1 = Advance(p1);
		}else if(Retrieve(p2) < Retrieve(p1)){
			Insert(Retrieve(p2),res,p);
			p2 = Advance(p2);
		}else{
			Insert(Retrieve(p1),res,p);
			p1 = Advance(p1);
			p2 = Advance(p2);
		}
		p = Advance(p);
	}

	while(p1){
		Insert(Retrieve(p1),res,p);
		p1 = Advance(p1);
		p = Advance(p);
	}

	while(p2){
		Insert(Retrieve(p2),res,p);
		p2 = Advance(p2);
		p = Advance(p);
	}

	link_list_print(res);

	return 0;
}
