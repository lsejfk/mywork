#include "BinTreeStruct.h"
#include "LinkStack.h"

//initialization
void initBinTree(BinTree **root){
	*root = NULL;
}
void visit(BinTreeElemType *e){
	printf("%4d",*e);
}

//Create the binary tree in preorder
void createBinTree(BinTree **root){
	BinTree *p;
	BinTreeElemType e;
	scanf("%d",&e);
	if(e == -1){
		*root = NULL;
	}else{
		p = (BinTree *)malloc(sizeof(BinTree));
		p->data = e;
		p->lchild = p->rchild = NULL;
		*root = p;
		createBinTree(&(p->lchild));		//create the left tree
		createBinTree(&(p->rchild));		//create the right tree
	}
}


//InOrderTraverse
void inOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e)){
	BinTree *p;
	LinkStack s;
	initLinkStack(&s);
	p = root;
	push(&s,p);			//push into stack
	while(!isEmpty(&s)){
		while(getTop(&s,&p),p != NULL){
			push(&s,p->lchild);
			p = p->lchild;	//push the left child until p = NULL
		}
		pop(&s,&p);		//pop the NULL value
		if(!isEmpty(&s)){
			pop(&s,&p);
			visit(&(p->data));	//visit the element
			push(&s,p->rchild);	//push the right child
		}
	}
}

//preOrderTraverse
void preOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e)){
	BinTree *p;
	LinkStack s;
	initLinkStack(&s);
	p = root;
	push(&s,p);
	while(!isEmpty(&s)){
		while(getTop(&s,&p),p!=NULL){
			visit(&(p->data));
			push(&s,p->lchild);
			p = p->lchild;
		}
		pop(&s,&p);		//pop the NULL value
		if(!isEmpty(&s)){
			pop(&s,&p);
			push(&s,p->rchild);
		}
	}
}

//postOrderTraverse
void postOrderTraverse(BinTree *root,void (*visit)(BinTreeElemType *e)){
	BinTree *p,*pre;
	LinkStack s;
	initLinkStack(&s);
	p = root;
	pre = NULL;
	push(&s,p);
	while(p!=NULL && !isEmpty(&s)){
		getTop(&s,&p);
		if((p->lchild == NULL && p->rchild == NULL) ||		//p is the leaf node
		(pre != NULL && (pre == p->rchild ||			//p's right child has been visited
		(pre == p->lchild && p->rchild == NULL)))){		//p's left child has been visited and p has no right child
			pop(&s,&p);
			visit(&(p->data));
			pre = p;
		}else{
			if(pre != p->lchild && p->lchild != NULL){	//left child is not NULL and p is not returned by its left child
				push(&s,p->lchild);
				p = p->lchild;
			}else if(p->rchild != NULL){
				push(&s,p->rchild);
				p = p->rchild;
			}
		}
	}
}

