#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	clock_t start,end;
	int i,j,k,n,sum;
	n = 1000;
	sum = 0;
	start = clock();
	for(i=0;i<n;i++)
		sum++;
	end = clock();
	printf("first:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);

	sum = 0;
	start = clock();
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			sum++;
		}
	}
	end = clock();
	printf("second:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);

	sum = 0;
	start = clock();
	for(i=0;i<n;i++){
		for(j=0;j<n*n;j++){
			sum++;
		}
	}
	end = clock();
	printf("third:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);

	sum = 0;
	start = clock();
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			sum++;
		}
	}
	end = clock();
	printf("fourth:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);

	sum = 0;
	start = clock();
	for(i=0;i<n;i++){
		for(j=0;j<i*i;j++){
			for(k=0;k<j;k++){
				sum++;
			}
		}
	}
	end = clock();
	printf("fifth:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);

	sum = 0;
	start = clock();
	for(i=1;i<n;i++){
		for(j=1;j<i*i;j++){
			if(j % i == 0){
				for(k=0;k<j;k++){
					sum++;
				}
			}
		}
	}
	end = clock();
	printf("sixth:%lf\n",(double)(end - start)/CLOCKS_PER_SEC);
	return 0;
}
