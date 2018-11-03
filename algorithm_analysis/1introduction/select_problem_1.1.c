/*
Find the k-th largest number in N numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Find the location of the new number in the k-th sorted numbers,
//if the new one less than the lowest in the numbers,throw away,and get another one.
void adjust_loc(int arr[],int k,int num){
	int i;
	if(k < 1 || num <= arr[k-1]){
		return;
	}
	for(i=k-2;i>=0&&num>arr[i];i--){
		arr[i+1] = arr[i];
	}
	if(i >= 0){
		arr[i] = num;
	}else{
		arr[0] = num;
	}
}

int comp(const void *a,const void *b){
	return (*((int *)a) - *((int *)b)) * (-1);
}


int main(int argc,char *argv[]){
	int num,count,capcity,inc;
	int i,k;
	int *arr;
	clock_t start,end;
	start = clock();
	/*
	if(argc != 2){
		fprintf(stderr,"usage:a.out <number>\n");
		return -1;
	}
	*/
	count = 0;
	capcity = 100;
	inc = 10;
	arr = (int *)malloc(sizeof(int) * capcity);
	while(scanf("%d",&num) != EOF){
		if(count < capcity){
			arr[count++] = num;
		}else{
			arr = (int *)realloc(arr,sizeof(int) * (capcity + inc));
			capcity += inc;
			arr[count++] = num;
		}
	}
	k = count / 2;
	qsort(arr,k,sizeof(int),comp);
	for(i=k;i<count;i++){
		adjust_loc(arr,k,arr[i]);
	}
	end = clock();
	printf("N = %d,The k-th number is %d time:%f\n",count,arr[k - 1],((double)(end - start)) / CLOCKS_PER_SEC);
	return 0;
}
