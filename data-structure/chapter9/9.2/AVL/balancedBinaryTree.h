#ifndef BALANCEDBINARYTREE_H
#define BALANCEDBINARYTREE_H
typedef int BSTNodeElemType;
typedef enum{LH=1,EH=0,RH=-1} BalancedFac;
typedef struct BSTNode{
	BSTNodeElemType data;		//Element
	BalancedFac bf;			//Balanced factor
	struct BSTNode *lchild;		//left child
	struct BSTNode *rchild;		//right child
}BSTNode,*BSTree;
int insertAVL(BSTree *t,BSTNodeElemType e,int *taller);
void leftBalance(BSTree *t);
void rightBalance(BSTree *t);
void initBinTree(BSTNode **root);
void visit(BSTNodeElemType *e);
void inOrderTraverse(BSTNode *root,void (*visit)(BSTNodeElemType *e));
void visit(BSTNodeElemType *e);
#endif
