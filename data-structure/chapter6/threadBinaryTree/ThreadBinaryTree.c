/*
This program is in chapter 6,named Clue Binary Tree
Then I product the operations the same as the Binary Tree
The characteristics of the Clue Binary Tree are as follow:
	If the program needs more option of traversing or finding the precursor and next node in the result of traversing,
	the structure is for you !
*/
#include "ThreadBinaryTree.h"

//create the binary tree
void createTBinTree(ThreadBinTree **root){
	ThBinTreeElemType e;
	ThreadBinTree *p;
	scanf("%d",&e);
	if(e == -1){				//-1 represents the NULL node
		*root = NULL;
	}else{
		p = (ThreadBinTree *)malloc(sizeof(ThreadBinTree));		//create the new node
		if(p == NULL){
			printf("error:createTBinTree:fail in malloc\n");
			return;
		}
		p->data = e;
		p->lTag = p->rTag = Link;
		p->lchild = p->rchild = NULL;
		*root = p;
		createTBinTree(&(p->lchild));	//create the left child tree
		createTBinTree(&(p->rchild));	//create the right child tree
	}
}

//clue the binary tree in order traversing
void inThreading(ThreadBinTree *root,ThreadBinTree **pre){
	ThreadBinTree *p = root;
	if(p != NULL){
		inThreading(p->lchild,pre);
		if(p->lchild == NULL){			//precursor clue
			p->lTag = Thread;
			p->lchild = *pre;
		}
		if((*pre)->rchild == NULL){		//successor clue
			(*pre)->rTag = Thread;
			(*pre)->rchild = p;
		}
		*pre = p;
		inThreading(p->rchild,pre);		//clue the left child tree
	}
}

//Clue the binary tree
void inOrderThreading(ThreadBinTree **threadRoot,ThreadBinTree *binRoot){
	ThreadBinTree *p,*pre;
	p = (ThreadBinTree *)malloc(sizeof(ThreadBinTree));		//create the head node
	if(p == NULL){
		printf("error:inOrderThreading:failed in malloc\n");
		return;
	}
	p->lTag = Link;
	p->rTag = Thread;
	p->rchild = p;
	*threadRoot = p;
	pre = *threadRoot;			//pre pointer to the last visited node relates to the current node
	if(binRoot == NULL){			//binRoot is an empty tree
		p->lchild = p;
	}else{
		p->lchild = binRoot;
		inThreading(binRoot,&pre);	//clue the binary tree in order traversing
		pre->rTag = Thread;
		pre->rchild = *threadRoot;
		(*threadRoot)->rchild = pre;
	}

}

void visit(ThBinTreeElemType *v){
	printf("%4d",*v);
}
//inOrderTraverse
void inOrderTraverse_th(ThreadBinTree *head,void (*visit)(ThBinTreeElemType *e)){
	ThreadBinTree *p;
	p = head->lchild;
	if(p == NULL){
		return;
	}
	while(p != head){
		while(p->lTag == Link){
			p = p->lchild;
		}
		visit(&(p->data));
		while(p->rTag == Thread && p->rchild != head){
			p = p->rchild;
			visit(&(p->data));
		}
		p = p->rchild;
	}
}
