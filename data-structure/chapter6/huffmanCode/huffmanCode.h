#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HuffmanCode{
	int weight;			//the path weight
	int parent;			//the subscript of parent
	int lchild;			//the subscript of left child
	int rchild;			//the subscirpt of right child
}HuffmanCode;
void huffman(HuffmanCode **ht,char ***hc,int weight[],int n);

void findHuffmanCode(HuffmanCode *ht,char ***hc,int n);

#endif
