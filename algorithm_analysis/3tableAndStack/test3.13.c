#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

#define ARR_NUM (sizeof(arr) / sizeof(arr[0]))
#define BUCKET_NUM 1000
#define SORT_TIMES 3
#define INIT_ARR_NUM 1000
#define ARR_INCRE 100 
void radix_sort(ElemType arr[],int n,int nbuckets,int sortTimes);

ElemType *creatArr(){
	ElemType *a;
	a = (ElemType *)calloc(INIT_ARR_NUM,sizeof(ElemType));
	if(a == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	return a;
}

int input_data(ElemType **a){
	int count = 0;
	ElemType e;
	static int top_num = INIT_ARR_NUM;
	while(scanf("%d",&e) != EOF){
		if(count >= top_num){
			*a = (ElemType *)realloc(*a,sizeof(ElemType)*(top_num + ARR_INCRE));
			if(*a == NULL){
				fprintf(stderr,"realloc failed\n");
				exit(-1);
			}
			top_num += ARR_INCRE;
		}
		(*a)[count++] = e;
	}
	return count;
}

void output_data(ElemType arr[],int n){
	int i;
	for(i=0;i<n;i++){
		printf("%ld ",arr[i]);
	}

}
int main(){
	ElemType *arr;
	int n;
	arr = creatArr();
	n = input_data(&arr);
	printf("%d\n",n);
	radix_sort(arr,n,BUCKET_NUM,SORT_TIMES);
	output_data(arr,n);
}



int get_index(ElemType e,int level){
	int i;
	long de;
	for(i=0;i<level;i++){
		e /= BUCKET_NUM;
	}
	return e % BUCKET_NUM;
}
void radix_sort(ElemType arr[],int n,int nbuckets,int sortTimes){
	List bucket[BUCKET_NUM];
	PtrToNode p;
	int i,j,k;
	for(i=0;i<nbuckets;i++){
		bucket[i] = CreateList();
	}

	for(i=0;i<SORT_TIMES;i++){
		for(j=0;j<nbuckets;j++){
			MakeEmpty(bucket[j]);
		}
		//allocate the array elements into buckets
		for(j=0;j<n;j++){
			InsertAsc(arr[j],bucket[get_index(arr[j],i)]);
		}
		k = 0;
		//collect the elements in buckets to the array
		for(j=0;j<nbuckets;j++){
			p = First(bucket[j]);
			while(p != NULL){
				arr[k++] = Retrieve(p);
				p = Advance(p);
			}
		}
	}//for
}
