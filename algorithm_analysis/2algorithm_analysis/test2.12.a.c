#include <stdio.h>
#include <stdlib.h>

int min_subset(int arr[],int n){
	int i,j,sum_min;
	sum_min = arr[0];
	j = 0;
	for(i=1;i<n;i++){
		if(sum_min <= arr[i]){
			if(i - j != 1){	//discontinuity
				continue;
			}
			if(arr[i] < 0){
				sum_min += arr[i];
				j = i;	//j record the last subsequence of sum_min
			}
		}else{
			sum_min = arr[i];
			j = i;
		}
	}
	return sum_min;
}

int main(){
	int arr[10] = {43,-2,34,5,-3,-1,4,56,-9,3};
	printf("min subset is %d\n",min_subset(arr,10));
	return 0;
}
