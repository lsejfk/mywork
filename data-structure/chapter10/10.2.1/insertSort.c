#include<stdio.h>

void insertSort(int arr[],int n){
	int i,j;
	for(i=2;i<=n;i++){
		if(arr[i] < arr[i-1]){
			arr[0] = arr[i];
			arr[i] = arr[i-1];
			for(j=i-2;j>0&&arr[0]<arr[j];j--){
				arr[j+1] = arr[j];	//Element backward
			}
			arr[j] = arr[0];		//Insertint
		}
	}
}
