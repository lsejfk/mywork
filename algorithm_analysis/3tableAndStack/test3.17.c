#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct List{
	int flag;
	ElemType data;
	struct List *next;
};

typedef struct List *LList;
typedef LList Position;
int GetNumOfElem(LList L);
int RmSame(LList L);
void Print(LList L);
void PrintLazy(LList L);
void Create(LList *list);
void DeleteL(LList L);

int main(){
	LList L;
	int same,total;
	Create(&L);
	same = RmSame(L);
	total = GetNumOfElem(L);
	if(same == (total - same)){
		DeleteL(L);
	}
	PrintLazy(L);
	Print(L);
}

void Create(LList *list){
	Position s;
	ElemType e;
	*list = (struct List *)malloc(sizeof(struct List));
	if(*list == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}

	(*list)->next = NULL;
	while(scanf("%d",&e) != EOF){
		s = (struct List *)malloc(sizeof(struct List));
		s->flag = 0;
		s->next = NULL;
		s->data = e;

		s->next = (*list)->next;
		(*list)->next = s;
	}
}

void DeleteL(LList L){
	Position p,q;
	for(q=L,p=L->next;p;){
		if(p->flag){
			q->next = p->next;
			free(p);
			p = q->next;
		}else{
			p = p->next;
			q = q->next;
		}
	}
}

void PrintLazy(LList L){
	Position p;
	for(p=L->next;p;p=p->next){
		printf("%d,",p->data);
	}
	printf("NULL\n");
}

void Print(LList L){
	Position p;
	for(p=L->next;p;p=p->next){
		if(p->flag == 0){
			printf("%d,",p->data);
		}
	}
	printf("NULL\n");
}


void LazyDelete(Position p){
	p->flag = 1;
}

int RmSame(LList L){
	Position p,q;
	int count = 0;
	for(p=L->next;p;p=p->next){
		for(q=p->next;q;q=q->next){
			if(p->data == q->data){
				LazyDelete(q);
				count++;
			}//if
		}//for q
	}//for p
	return count;
}

int GetNumOfElem(LList L){
	Position p;
	int count = 0;
	for(p=L->next;p;p=p->next){
		count++;
	}
	return count;
}
