#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned int myrand(unsigned int i,unsigned int j);
void swap(unsigned int *a,unsigned int *b);
void rand_traverse1(unsigned int n);
void rand_traversel2(unsigned int n);
void rand_traversel3(unsigned int n);

int main(){
	unsigned int n;
	clock_t start,end;
	scanf("%d",&n);
	start = clock();
	rand_traverse1(n);
	end = clock();
	printf("first:%f\n",(double)(end - start)/CLOCKS_PER_SEC);

	start = clock();
	rand_traversel2(n);
	end = clock();
	printf("second:%f\n",(double)(end - start)/CLOCKS_PER_SEC);

	start = clock();
	rand_traversel3(n);
	end = clock();
	printf("third:%f\n",(double)(end - start)/CLOCKS_PER_SEC);
	return 0;
}

//Creat myrand numbers
unsigned int myrand(unsigned int i,unsigned int j){
	srand(time(NULL));
	return (i + (rand() % (j - i + 1)));
}

//algorithm 1
void rand_traverse1(unsigned int n){
	unsigned int i,j,rand;
	unsigned int *arr;
	if((arr = (unsigned int *)calloc(sizeof(unsigned int),n)) == NULL){
		return;
	}
	for(i=0;i<n;i++){
		rand = myrand(1,n);
		for(j=0;j<i;j++){
			if(rand == arr[j]){	//This rand number has been used
				rand = myrand(1,n);
				j = 0;		//return to 0,re-examination
			}
		}
		arr[i] = rand;
	}
}


//algorithm 2
void rand_traversel2(unsigned int n){
	unsigned int i,j,rand;
	unsigned int *arr,*used;
	if((arr = (unsigned int *)calloc(sizeof(unsigned int),n)) == NULL || 
		(used = (unsigned int *)calloc(sizeof(unsigned int),n + 1)) == NULL){
		return;
	}
	for(i=0;i<n+1;i++){
		used[i] = 0;		//initialize to unused
	}
	for(i=0;i<n;i++){
		rand = myrand(1,n);
		while(used[rand]){	//It has been used,creat a new one
			rand = myrand(1,n);
		}
		arr[i] = rand;
		used[rand] = 1;
	}
}


//algorithm 3
void rand_traversel3(unsigned int n){
	unsigned int i,j;
	unsigned int *arr;
	if((arr = (unsigned int *)calloc(sizeof(unsigned int),n)) == NULL){
		return;
	}
	for(i=1;i<n;i++){
		swap(&arr[i],&arr[myrand(0,i)]);
	}
}

//swap
void swap(unsigned int *a,unsigned int *b){
	unsigned int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
