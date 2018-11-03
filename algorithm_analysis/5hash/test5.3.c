#include <stdio.h>
#include <stdlib.h>


int nextprime(int the){
	int k,res;
	if(the < 3){
		return 2;
	}else if(the < 5){
		return 3;
	}else if(the < 7){
		return 5;
	}else{
		k = the / 6;
		if((res = 6 * k + 1) >= the){
			return res;
		}else if((res = 6 * k + 5) >= the){
			return res;
		}
	}
	return the;
}

int forwardprime(int the){
	int k,res;
	if(the < 2){
		return -1;
	}else if(the < 3){
		return 2;
	}else if(the < 5){
		return 3;
	}else if(the < 7){
		return 5;
	}else{
		k = the / 6;
		res = 6 * k + 1;
		if(the != res){
			return res;
		}
		return 6 * (k - 1) + 5;

	}
	return the;
}

int lineardete(int *arr,int n){
	int flag[10001];
	int i,count,size,index;

	for(i=0;i<10001;i++){
		flag[i] = 0;
	}
	count = 0;
	size = nextprime(n);
	for(i=0;i<n;i++){
		index = arr[i] % size;
		while(flag[index]){
			count++;
			index++;
			if(index >= size){
				index -= size;
			}
		}
		flag[index] = 1;
	}
	return count;
}

int squaredete(int *arr,int n){
	int flag[10001];
	int i,count,size,k,index;

	for(i=0;i<10001;i++){
		flag[i] = 0;
	}
	count = 0;
	size = nextprime(n);

	for(i=0;i<n;i++){
		index = arr[i] % n;
		k = 0;
		while(flag[index]){
			count++;
			index  += 2 * ++k - 1;
			if(index >= size){
				index -= size;
			}
		}
		flag[i] = 1;
	}
	return count;
}

int doublehash(int *arr,int n){
	int flag[10001];
	int i,count,size,k,r,hash2,save;
	unsigned int index;

	for(i=0;i<10001;i++){
		flag[i] = 0;
	}

	count = 0;
	size = nextprime(n);
	r = forwardprime(size);
	

	for(i=0;i<n;i++){
		index = arr[i] % n;
		save = index;
		hash2 = r - arr[i] % r;
		k = 0;
		while(flag[index]){
			count++;
			index = save  + ++k * hash2;
			if(index >= size){
				index %= size;
			}
		}
		flag[i] = 1;
	}
	return count;
}

int main(){
	int flag[10001],arr[10001];
	int i,e,n,count;

	i = 0;
	while(scanf("%d",&e) != EOF){
		arr[i++] = e;
	}
	n = i;

	printf("linear detection:%d\n",lineardete(arr,n));
	printf("square detection:%d\n",squaredete(arr,n));
	printf("double hash:%d\n",doublehash(arr,n));
	return 0;
}
