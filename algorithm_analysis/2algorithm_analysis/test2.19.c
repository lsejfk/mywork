#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int ElemType;

int is_even(int n){
	return (n % 2 == 0) ? 1 : 0;
}
int isBadserial(ElemType arr[],int start){
	if(arr[start] == arr[start+1] && arr[start] == arr[start+2]){
		return 1;
	}else{
		return 0;
	}
}

void getKey(ElemType arr[],int start,int *k){
	if(arr[start] == arr[start+1]){
		arr[(*k)++] = arr[start];
	}else if(arr[start] == arr[start+2]){
		arr[(*k)++] = arr[start];
	}else if(arr[start+1] == arr[start+2]){
		arr[(*k)++] = arr[start+1];
	}
}
int find_key_elem(ElemType arr[],int n,ElemType *elem){
	int k,i;
	int flag = 1;
	if(n == 1){
		*elem = arr[0];
		return 1;	//the key exists
	}
	if(n == 0){
		*elem = 0;
		return 0;	//the key doesn't exist
	}
	k = 0;
	if(is_even(n)){
		for(i=0;i<n;i+=2){
			if(arr[i] == arr[i+1]){
				arr[k++] = arr[i];	//candidate element
			}
		}
		return find_key_elem(arr,k,elem);
	}else{		//odd
		i = 0;
		while(n > 0){
			if(flag){			//haven't handled the group with three elements
				if(isBadserial(arr,i)){		//three elements starting from i are equal
					arr[k++] = arr[i];	//candidate element
					i += 2;
					n -= 2;			//remain elements
				}else{
					getKey(arr,i,&k);	//get the key from three elements
					i += 3;
					n -= 3;
					flag = 0;		//having handled the group with three element
				}//if isBadserial
			}else{//if flag
				if(arr[i] == arr[i+1]){
					arr[k++] = arr[i];
				}
				i += 2;
				n -= 2;
			}//if flag
		}//while n
		return find_key_elem(arr,k,elem);
	}//if is_even
}

int main(){
	ElemType arr[100],elem;
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	if(find_key_elem(arr,n,&elem)){
		printf("key elem is %d\n",elem);
	}else{
		printf("no key in the arr\n");
	}
	return 0;
}
