#include <stdio.h>
#include <stdlib.h>

struct Poly_tag{
	int coff;
	int exp;
	struct Poly_tag *next;
};

typedef struct Poly_tag *Poly;

struct Node_tag{
	struct Poly_tag *p;
};

struct List_tag{
	int listsize;
	struct Node_tag *list;
};	

Poly create(){
	int coff,exp,flag;
	Poly p,q,head;
	flag = 1;
	while(scanf("%d%d",&coff,&exp) != EOF){
		q = (Poly)malloc(sizeof(struct Poly_tag));
		if(q == NULL){
			fprintf(stderr,"malloc failed\n");
			exit(-1);
		}
		q->coff = coff;
		q->exp = exp;
		q->next = NULL;
		if(flag){
			head = q;
			flag = 0;
		}else{
			p->next = q;
		}
		p = q;
	}
	return head;
}

struct List_tag *list_init(int listsize){
	struct List_tag *p;
	int i;
	if(listsize < 1){
		fprintf(stderr,"listsize is too small\n");
		return NULL;
	}
	p = (struct List_tag *)malloc(sizeof(struct List_tag));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->listsize = listsize;
	p->list = (struct Node_tag *)calloc(listsize,sizeof(struct Node_tag));
	if(p->list == NULL){
		fprintf(stderr,"calloc failed\n");
		exit(-1);
	}
	for(i=0;i<listsize;i++){
		p->list[i].p = NULL;
	}
	return p;
}


int main(){
	struct List_tag *L;
	Poly p1,p2,q1,q2,s;
	struct Poly_tag *p;
	int size,i;
	p1 = create();
	p2 = create();
	scanf("%d",&size);
	L = list_init(size);
	for(q1=p1;q1;q1=q1->next){
		for(q2=p2;q2;q2=q2->next){
			if(L->list[q1->exp + q2->exp].p == NULL){
				s = (Poly)malloc(sizeof(struct Poly_tag));
				if(s == NULL){
					fprintf(stderr,"malloc failed\n");
					exit(-1);
				}
				s->coff = q1->coff * q2->coff;
				s->exp = q1->exp + q2->exp;
				s->next = NULL;
				L->list[s->exp].p = s;
			}else{
				p = L->list[q1->exp + q2->exp].p;
				p->coff += q1->coff * q2->coff;
			}
		}//for q2
	}//for q1

	for(i=0;i<size;i++){
		if(L->list[i].p){
			printf("%d * 10 ^ %d + ",L->list[i].p->coff,L->list[i].p->exp);
		}
	}
	printf("0\n");
	return 0;
}
