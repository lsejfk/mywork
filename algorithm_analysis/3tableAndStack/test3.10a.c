#include <stdio.h>
#include <stdlib.h>

struct Josephus{
	int seq;
	struct Josephus *next;
};

int main(){
	struct Josephus *p,*q,*s,*fore;
	int m,n,i,count,j;
	scanf("%d%d",&m,&n);

	m = m % n;
	count = n;
	i = 1;
	//create a circle
	p = (struct Josephus *)malloc(sizeof(struct Josephus));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		return -1;
	}
	p->seq = i++;
	q = p;
	while(--count > 0){
		s = (struct Josephus *)malloc(sizeof(struct Josephus));
		if(s == NULL){
			fprintf(stderr,"malloc failed\n");
			return -1;
		}
		s->seq = i++;
		q->next = s;
		s->next = p;
		q = q->next;
	}

	fore = q;
	count = n;
	j = m;
	while(count > 1){
		j = m;
		while(j-- > 0){		//find the location where the person will be out
			p = p->next;
			fore = fore->next;
		}

		printf("%d,",p->seq);
		//remove
		fore->next = p->next;
		free(p);
		p = fore->next;
		count--;
	}
	printf("\n%d\n",p->seq);
	/*
	arr = (int *)calloc(n,sizeof(int));
	if(arr == NULL){
		fprintf(stderr,"calloc failed\n");
		return -1;
	}
	for(i=0;i<n;i++){
		arr[i] = 0;		//haven't out
	}
	count = n;
	i = m % n;
	while(count > 1){
		j = m;
		while(j > 0){
			if(arr[i] == 0){
				j--;
				i = (i + 1) % n;
			}else{
				i = (i + 1)  % n;
			}
		}
		if(arr[i] == 0){
			arr[i] = 1;
			count--;
			printf("%d,",i+1);
		}
		
		i = (i + 1) % n;
		while(arr[i] == 1){
			i = (i + 1) % n;
		}
	}
	printf("\n");
	for(i=0;i<n;i++){
		if(arr[i] == 0){
			printf("%d\n",i+1);
		}
	}
	*/
	return 0;
}
