#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

struct List{
	ElemType e;
	struct List *next;
};

struct List *find(struct List *head,ElemType e){
	struct List *p;
	p = head->next;
	while(p){
		if(p->e == e){
			return p;
		}
		p = p->next;
	}
	return NULL;
}

struct List *findRecur(struct List *p,ElemType e){
	if(p == NULL){
		return NULL;
	}
	if(p->e == e){
		return p;
	}
	return findRecur(p->next,e);
}

int main(int argc,char *argv[]){
	int i,j;
	struct List *p,*s,*head;
	if(argc != 4){
		fprintf(stderr,"usage:a.out <type> <elem> <num>\n");
		return -1;
	}

	head = (struct List *)malloc(sizeof(struct List));
	if(head == NULL){
		fprintf(stderr,"malloc failed\n");
		return -1;
	}
	head->next = NULL;
	p = head;
	//create the list
	for(i=0;i<atoi(argv[3]);i++){
		s = (struct List *)malloc(sizeof(struct List));
		if(s == NULL){
			fprintf(stderr,"malloc failed\n");
			return -1;
		}
		s->e = i+1;
		s->next = NULL;
		p->next = s;
		p = p->next;
	}
	

	if(strcmp(argv[1],"norecur") == 0){
		printf("function find:\n");
		p = find(head,atoi(argv[2]));
		if(p){
			printf("find the element %d\n",p->e);
		}else{
			printf("no such element\n");
		}
	}else if(strcmp(argv[1],"recur") == 0){
		printf("function findRecur:\n");
		p = findRecur(head->next,atoi(argv[2]));
		if(p){
			printf("find the element %d\n",p->e);
		}else{
			printf("no such element\n");
		}
	}

	
}
