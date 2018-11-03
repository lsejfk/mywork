#include<stdio.h>
#include<stdlib.h>

void shellInsert(int arr[],int dk,int n){
	int i,j;
	for(i=dk+1;i<=n;i++){
		if(arr[i] < arr[i-dk]){
			arr[0] = arr[j];
			for(j=i-dk;j>0&&arr[0]<arr[j];j-=dk){
				arr[j+dk] = arr[j];		//Element backward
			}
			arr[j+dk] = arr[0];			//Inserting
		}
	}
}
