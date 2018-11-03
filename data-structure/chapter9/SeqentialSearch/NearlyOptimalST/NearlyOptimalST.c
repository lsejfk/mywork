#include "SequentialTable.h"
#include<math.h>
#include<stdlib.h>
#include<assert.h>

//construct Nearly Optimal Search Tree
void secondOptimal(BinTree **tree,SSTable *tab,double sw[],int low,int high){
	int i,j;
	double min,dw;
	BinTree *p;
	i = low;
	min = abs(sw[high] - sw[low]);			//op = sw[high] + sw[low-1] - sw[i] - sw[i-1]
	dw = sw[high] + sw[low - 1];
	for(j=low+1;j<=high;j++){			//choose the minimum of op
		if(abs(dw - sw[j] - sw[j-1]) < min){
			i = j;
			min = abs(dw - sw[j] - sw[j-1]);
		}
	}
	p = (BinTree *)malloc(sizeof(BinTree));
	assert(p != NULL);
	p->data = tab->elem[i].data;
	*tree = p;
	if(i == low){
		p->lchild = NULL;			//the left child is NULL
	}else{
		secondOptimal(&(p->lchild),tab,sw,low,i-1);
	}
	if(i == high){
		p->rchild = NULL;
	}else{
		secondOptimal(&(p->rchild),tab,sw,i+1,high);
	}
}

//find the value of sw
void findSW(double sw[],SSTable *tab){
	int i;
	sw[0] = 0;
	for(i=1;i<=tab->length;i++){
		sw[i] = tab->elem[i].weight + sw[i-1];
	}
}

void createSOSTree(SOSTree **tree,SSTable *tab){
	double *sw;
	sw = (double *)malloc(sizeof(double) * (tab->length + 1));
	assert(sw != NULL);
	if(tab->length == 0){
		*tree = NULL;
	}else{
		findSW(sw,tab);					//find the value of sw
		secondOptimal(tree,tab,sw,1,tab->length);
	}
}
