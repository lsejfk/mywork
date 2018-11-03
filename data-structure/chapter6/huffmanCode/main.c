#include "huffmanCode.h"

int main(){
	char **hc,**hnewc;
	int i,n;
	HuffmanCode *ht;
	int w[] = {0,5,29,7,8,14,23,3,11};
	n = 8;
	huffman(&ht,&hc,w,8);
	printf("%-4s\t%-4s\t%-4s\t%-4s\t%-4s\t\n","xx","weight","parent","lchild","rchild");
	for(i=1;i<=2*n-1;i++){
		printf("%-10d%-10d %-10d %-10d %-10d\n",i,ht[i].weight,ht[i].parent,ht[i].lchild,ht[i].rchild);
	}

	printf("the huffman code:\n");
	for(i=1;i<=n;i++){
		printf("%-4d%-4s\n",i,hc[i]);
	}
	findHuffmanCode(ht,&hnewc,n);
	printf("the new code:\n");
	for(i=1;i<=n;i++){
		printf("%-4d%-4s\n",i,hc[i]);
	}

	return 0;
}
