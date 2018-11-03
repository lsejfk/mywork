#include <stdio.h>
#include <stdlib.h>

typedef char SonBroElemType;

struct SonBroTree{
	SonBroElemType elem;
	struct SonBroTree *son;
	struct SonBroTree *brother;
};

typedef struct SonBroTree *SBTree;
typedef SBTree SBTreePtr;

static SBTree makenode(SonBroElemType ch){
	SBTree p;
	p = (SBTree)malloc(sizeof(struct SonBroTree));
	if(p == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	p->elem = ch;
	p->son = p->brother = NULL;
	return p;
}

static void sbt_buildTree(SBTree *T){
	SBTreePtr p;
	char ch;
	scanf("%c",&ch);
	if(ch == '#'){
		*T = NULL;
	}else{
		p = makenode(ch);
		*T = p;
		sbt_buildTree(&((*T)->son));
		sbt_buildTree(&((*T)->brother));
	}
}

static void printSBTree(SBTree T){
	if(T){
		printf("%c ",T->elem);
		printSBTree(T->son);
		printSBTree(T->brother);
	}
}

static int isSimilar(SBTree T1,SBTree T2){
	if(T1 == NULL && T2 == NULL){
		return 1;
	}

	if(T1 && T2){
		return isSimilar(T1->son,T2->son) && isSimilar(T1->brother,T2->brother);
	}
	return 0;
}

int main(){
	SBTree T1,T2;
	sbt_buildTree(&T1);
	printSBTree(T1);
	printf("\n");
	getchar();
	sbt_buildTree(&T2);
	printSBTree(T2);
	printf("\n");
	if(isSimilar(T1,T2)){
		printf("similar\n");
	}else{
		printf("no\n");
	}
	return 0;
}
