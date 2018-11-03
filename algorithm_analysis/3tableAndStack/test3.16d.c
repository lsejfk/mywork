#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_LIST 1000
void rm_same(List L);

int main(){
	List L;
	Create(&L);
	link_list_print(L);
	rm_same(L);
	link_list_print(L);
	return 0;
}

int cmp(const void *a,const void *b){
	return (*((ElemType *)a) - *((ElemType *)b));
}

int insert_arr(ElemType arr[],ElemType x){
	static int n = 0;
	int i,j;
	for(i=0;i<n && x > arr[i];i++)
		;
	for(j=n;j>i;j--){
		arr[j] = arr[j-1];
	}
	arr[i] = x;
	return ++n;
}

void rm_same(List L){
	ElemType arr[NUM_LIST],e;
	Position p,q;
	int n;
	int i;
	for(n=0,p=First(L);p;){
		e = Retrieve(p);
		if(bsearch(&e,arr,n,sizeof(arr[0]),cmp)){	//success
			q = Advance(p);
			Delete(p,L);
			p = q;
		}else{
			n = insert_arr(arr,e);
			p = Advance(p);
		}

	}//for
}


