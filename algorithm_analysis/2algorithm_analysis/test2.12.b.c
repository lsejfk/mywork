#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int pos_min_subset(int arr[],int n){
	int min,sum;
	int i,j;
	min = INT_MAX;
	for(i=0;i<n;i++){
		sum = 0;
		for(j=i;j<n;j++){
			sum += arr[j];
			if(sum > 0 && sum < min){
				min = sum;
			}
		}//for j
	}//for i		
}
struct item{
	int index;
	int value;
};
//
int cmp(const void *a,const void *b){
	struct item *sa,*sb;
	sa = (struct item *)a;
	sb = (struct item *)b;
	if(sa->value == sb->value){		//merge into the lower index when the two element'value is equal
		sa->index = sb->index = sa->index < sb->index ? sa->index : sb->index;
	}
	return sa->value - sb->value;
}
//nlogn
int pos_min_subset2(int arr[],int n){
	struct item a[100];
	int i,thisSum;
	int min;
	thisSum = 0;
	for(i=0;i<n;i++){
		thisSum += arr[i];
		a[i].index = i;
		a[i].value = thisSum;	//find the sum of the first n element
	}
	qsort(a,n,sizeof(a[0]),cmp);	//sort by item.value
	min = a[0].value > 0 ? a[0].value : INT_MAX;

	for(i=1;i<n;i++){
		if(a[i].index > a[i-1].index && (a[i].value - a[i-1].value > 0) && (a[i].value - a[i-1].value < min)){
			min = a[i].value - a[i-1].value;
		}
	}
	return min;
}

int main(){
	int n,arr[100];
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("the minimal subset is %d\n",pos_min_subset2(arr,n));
	return 0;	
}
