#include <stdio.h>
#include <stdlib.h>

int main(){
	int nums,i,k,tmp,child,j,laseval,minval;
	int arr[100];
	scanf("%d%d",&k,&nums);
	for(i=1;i<=nums;i++){
		scanf("%d",&arr[i]);
	}
	//build heap
	for(i=nums/2;i>0;i--){
		child = i * 2;
		if(child != nums && arr[child + 1] < arr[child]){
			child++;
		}
		if(arr[i] > arr[child]){
			tmp = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}
	}

	//do k times deleteMin
	for(i=0;i<k;i++){
		if(nums <= 0){
			break;
		}
		laseval = arr[nums--];
		minval = arr[1];
		for(j=1;j*2<=nums;j=child){
			child = 2 * j;
			if(child != nums && arr[child+1] < arr[child]){
				child++;
			}
			if(laseval > arr[child]){
				arr[j] = arr[child];
			}else{
				break;
			}
		}
		arr[j] = laseval;
	}

	printf("%d\n",minval);
	return 0;
}
