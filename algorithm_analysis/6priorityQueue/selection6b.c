#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	PriorityQueue H;
	int k,i,nums,e;
	scanf("%d%d",&k,&nums);
	if(k > nums){
		fprintf(stderr,"k is too big\n");
		return -1;
	}
	H = priq_init(k);
	for(i=0;i<k;i++){
		scanf("%d",&e);
		priq_insert(e,H);
	}
	for(;i<nums;i++){
		scanf("%d",&e);
		if(e > priq_findMin(H)){
			priq_deleteMin(H);
			priq_insert(e,H);
		}
	}
	printf("%d",priq_findMin(H));
	return 0;
}
