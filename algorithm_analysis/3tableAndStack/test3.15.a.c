#include <stdio.h>
#include <stdlib.h>

#define SPACESIZE 100 

typedef int PtrToNode;
typedef PtrToNode Position;
typedef int ElemType;
typedef Position List;

struct StaticList{
	ElemType e;
	Position next;
};

struct StaticList CursorSpace[SPACESIZE]; 

Position findPrevious(List s,Position p);
void selfAdjust(List s,Position p);
Position allocspace();
void insert_cur(List s,ElemType x);
List init_cur_space();
Position findValue(List s,ElemType x);
void print_list(List s);

int main(){
	List s;
	ElemType e;
	s = init_cur_space();
	while(scanf("%d",&e) != EOF){
		insert_cur(s,e);
	}
	print_list(s);
	findValue(s,99);
	print_list(s);
}

void print_list(List s){
	Position p;
	for(p=CursorSpace[s].next;p;p=CursorSpace[p].next){
		printf("%d,",CursorSpace[p].e);
	}
	printf("\n");
}

Position findValue(List s,ElemType x){
	Position q;
	for(q=CursorSpace[s].next;q && CursorSpace[q].e != x;q=CursorSpace[q].next)
		;
	
	if(q){
		selfAdjust(s,q);
	}
	return q;
}

List init_cur_space(){
	int i;
	CursorSpace[0].next = 2;
	CursorSpace[1].next = 0;
	for(i=2;i<SPACESIZE-1;i++){
		CursorSpace[i].next = i + 1;
	}
	CursorSpace[i].next = 0;
	return 1;
}

void insert_cur(List s,ElemType x){
	Position p;
	p = allocspace();
	if(p == 0){
		fprintf(stderr,"insert failed:space is full\n");
		exit(-1);
	}
	CursorSpace[p].e = x;

	CursorSpace[p].next = CursorSpace[s].next;
	CursorSpace[s].next = p;
}

Position allocspace(){
	Position p;
	p = CursorSpace[0].next;
	CursorSpace[0].next = CursorSpace[p].next;
	return p;
}

void selfAdjust(List s,Position p){
	Position pre;
	pre = findPrevious(s,p);

	//delete p
	CursorSpace[pre].next = CursorSpace[p].next;
	//insert p
	CursorSpace[p].next = CursorSpace[s].next;
	CursorSpace[s].next = p;
}

Position findPrevious(List s,Position p){
	Position q;
	for(q=s;q && CursorSpace[q].next != p;q=CursorSpace[q].next)
		;
	return q;
}
