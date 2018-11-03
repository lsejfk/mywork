#include "binarySortTree.h"

//Recursively look for data elements whose keyword 
//is equal to key in the Binary Sort Tree 
//referred to by the root pointer t
int searchBST(BinTree *t,BinTreeElemType key,BinTree *f,BinTree **p){
	if(t == NULL){			//Failed in searching
		*p = f;
		return 0;
	}
	if(t->data == key){		//Find the key
		*p = t;
		return 1;
	}else if(key < t->data){	//Recursively search the left tree
		return (searchBST(t->lchild,key,t,p));
	}else{				//Recursively search the right tree
		return (searchBST(t->rchild,key,t,p));
	}
}

//Insert elements while the key is not exist in the binary sort tree
int insertBST(BinTree **t,BinTreeElemType data){
	BinTree *p,*q;
	q = NULL;
	if(!(searchBST(*t,data,NULL,&q))){
		p = (BinTree *)malloc(sizeof(BinTree));
		p->data = data;
		p->lchild = p->rchild = NULL;
		if(q == NULL){			
			*t = p;		//Build a new node for the binary sort tree
		}else if(data < q->data){	//Insert into left child
			q->lchild = p;
		}else{				//Insert into right child 
			q->rchild = p;
		}
		return 1;
	}else{
		return 0;
	}
}


//delete node p from binary sort tree
int deleteNode(BinTree **p){
	BinTree *q,*s;
	if((*p)->rchild == NULL){		//Rebuild left tree
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}else if((*p)->lchild == NULL){		//Rebuild right tree
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}else{					//Each side of the binary sort tree isn't NULL
		q = *p;
		s = q->lchild;
		while(s->rchild != NULL){	//Go to the node which has no right child
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;		//Delete node s
		if(q != *p){
			q->rchild = s->lchild;
		}else{
			q->lchild = s->lchild;
		}
		free(s);
	}
	return 1;
}

//If there exists element data equals to key,then delete the element from the binary sort tree
int deleteBST(BinTree **t,BinTreeElemType key){
	BinTree *p;
	if(*t == NULL){				//Find no key
		return 0;
	}else if((*t)->data == key){
		return deleteNode(t);
	}else if(key < (*t)->data){
		return deleteBST(&((*t)->lchild),key);
	}else{
		return deleteBST(&((*t)->rchild),key);
	}
}
