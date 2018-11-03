#include "myerr.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	List L1,L2;
	Position p1,p2,pos;
	List res;
	Create(&L1);
	Create(&L2);
	res = CreateList();
	pos = Header(res);
	
	p1 = First(L1);
	p2 = First(L2);

	while(p1 && p2){
		if(Retrieve(p1) < Retrieve(p2)){
			p1 = Advance(p1);
		}else if(Retrieve(p2) < Retrieve(p1)){
			p2 = Advance(p2);
		}else{
			Insert(Retrieve(p1),res,pos);
			pos = Advance(pos);
			p1 = Advance(p1);
			p2 = Advance(p2);
		}
	}
	link_list_print(res);
	return 0;
}
