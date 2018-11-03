#include <stdio.h>
#include <stdlib.h>

static int numofnodes(Tree T){
	int nleft,nright;
	if(T == NULL){
		return 0;
	}else{
		nleft = numofnodes(T->left);
		nright = numofnodes(T->right);
		return nleft + nright + 1;
	}
}

static int numofleaves(Tree T){
	static int count = 0;
	if(T == NULL){
		return 0;
	}else if(T->left == NULL && T->right == NULL){
		count++;
	}else{
		numofleaves(T->left);
		numofleaves(T->right);
	}
	return count;
}

static int numoffullnode(Tree T){
	static int count = 0;
	if(T == NULL){
		return 0;
	}else if(T->left && T->right){
		count++;
	}
	numoffullnode(T->left);
	numoffullnode(T->right);
	return count;
}
