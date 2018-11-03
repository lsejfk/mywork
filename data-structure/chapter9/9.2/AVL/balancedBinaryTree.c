#include "balancedBinaryTree.h"
#include<stdlib.h>
#include<assert.h>

//Right rotate
void r_rotate(BSTree *p){
	BSTree lc;
	lc = (*p)->lchild;		//The root node of the left subtree of p pointed to by lc
	(*p)->lchild = lc->rchild;	//The right subtree of lc is attached to the left subtree of p
	lc->rchild = *p;		
	*p = lc;			//p point to the new root node
}

//Left rotate
void l_rotate(BSTree *p){
	BSTree rc;
	rc = (*p)->rchild;		//The root node of the right subtree of p pointed to by rc
	(*p)->rchild = rc->lchild;	//The left subtree of lc is attached to the right subtree of p
	rc->lchild = *p;
	*p = rc;			//p point to the new root node
}

//If there doesn't exist one key in a Balanced Sort Tree equals to e
//then insert e into the tree,if the tree becomes imbalance,rotate until it balanced
int insertAVL(BSTree *t,BSTNodeElemType e,int *taller){
	if(*t == NULL){			//insert e into the tree
		*t = (BSTNode *)malloc(sizeof(BSTNode));
		assert(*t != NULL);
		(*t)->data = e;
		(*t)->lchild = (*t)->rchild = NULL;
		(*t)->bf = EH;
		*taller = 1;		//Indicate that the tree grows taller after inserting one element
	}else{
		if(e == (*t)->data){
			*taller = 0;
			return 0;
		}else if(e < (*t)->data){	//Insert into left subtree
			if(!(insertAVL(&((*t)->lchild),e,taller))){	//Failed in inserting e
				return 0;
			}
			if(*taller){	//Readjust the balanced factor
				switch((*t)->bf){
					case LH :
						leftBalance(t);	//Adjust in order to rebuild a balanced tree
						*taller = 0;	//The tree won't grow taller after adjusting
						break;
					case EH :
						(*t)->bf = LH;
						*taller = 1;
						break;
					case RH :
						(*t)->bf = EH;
						*taller = 0;
						break;
				}//switch((*t)->bf)
			}//if(*taller)

		}else{
			if(!(insertAVL(&((*t)->rchild),e,taller))){
				*taller = 0;
				return 0;
			}
			if(*taller){
				switch((*t)->bf){
					case LH :
						(*t)->bf = EH;
						*taller = 0;
					break;
					case EH :
						(*t)->bf = RH;
						*taller = 1;
					break;
					case RH :
						rightBalance(t);
						*taller = 0;
					break;
				}//switch((*t)->bf)
			}//if(*taller)
		}//else
	}//else *t == NULL
}

//Left-balanced rotalation of a binary tree with the root of the node 
//pointed to by the pointer t
void leftBalance(BSTree *t){
	BSTree lc,rd;
	lc = (*t)->lchild;		//The root node's left child node is pointed to by lc
	switch(lc->bf){
		case LH :
			(*t)->bf = lc->bf = EH;
			r_rotate(t);	//Right rotate
			break;
		case RH :		//It needs to rotate leftly first,and then rotate rightly
			rd = lc->rchild;
			switch(rd->bf){
				case LH :
					(*t)->bf = RH;
					lc->bf = EH;
					break;
				case EH :
					(*t)->bf = lc->bf = EH;
					break;
				case RH :
					(*t)->bf = EH;
					lc->bf = LH;
					break;
			}//switch(rd->bf)
			rd->bf = EH;
			l_rotate(&((*t)->lchild));
			r_rotate(t);
			break;
	}//switch(lc->bf)
}


//Right-balanced rotalation of a binary tree with the root of the node 
//pointed to by the pointer t
void rightBalance(BSTree *t){
	BSTree rc,ld;
	rc = (*t)->rchild;
	switch(rc->bf){
		case RH :		//Only needs to rotate leftly
			rc->bf = (*t)->bf = EH;
			l_rotate(t);
			break;
		case LH :		//It needs to rotate rightly first,and then rotate leftly
			ld = rc->lchild;
			switch(ld->bf){
				case LH :
					(*t)->bf = EH;
					rc->bf = RH;
					break;
				case EH :
					(*t)->bf = rc->bf = EH;
					break;
				case RH :
					(*t)->bf = LH;
					rc->bf = EH;
					break;
			}//switch(ld->bf)
			ld->bf = EH;
			r_rotate(&((*t)->rchild));
			l_rotate(t);
	}//switch(rc->bf)
}
