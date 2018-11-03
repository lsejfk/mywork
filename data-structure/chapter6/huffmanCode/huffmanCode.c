#include "huffmanCode.h"

//choose two minimum weight among 1 to i-1
void chooseTNode(HuffmanCode *ht,int num,int *sub1,int *sub2){
	int i,flag = 0,s1,s2;
	for(i=1;i<=num;i++){			//initialize s1 and s2
		if(ht[i].parent == 0){
			if(flag == 0){
				s1 = i;
				flag++;
			}else if(flag == 1){
				s2 = s1;
				if(ht[i].weight < ht[s1].weight){
					s1 = i;
				}else{
					s2 = i;
				}
				flag++;
			}else{
				break;
			}
		}
	}
	for(;i<=num;i++){			//traverse the array and find the two minimun weight
		if(ht[i].parent != 0){
			continue;
		}
		if(ht[i].weight < ht[s1].weight){
			s2 = s1;
			s1 = i;
		}else if(ht[i].weight < ht[s2].weight){
			s2 = i;
		}
	}
	*sub1 = s1;
	*sub2 = s2;
}

//create the huffman table ht and find the code
void huffman(HuffmanCode **ht,char ***hc,int weight[],int n){
	int m,i,j,f,start,s1,s2;
	char *cd;
	HuffmanCode *p;
	char **q;
	m = 2 * n - 1;			//the total nodes of huffman tree
	*ht = (HuffmanCode *)malloc(sizeof(HuffmanCode) * (m + 1));	//the first one unused
	p = *ht;
	for(i=1;i<=n;i++){		//initialization
		p[i].weight = weight[i];
		p[i].parent = 0;
		p[i].lchild = 0;
		p[i].rchild = 0;
	}
	for(i=n+1;i<=m;i++){
		p[i].weight = 0;
		p[i].parent = 0;
		p[i].lchild = 0;
		p[i].rchild = 0;
	}

	for(i=n+1;i<=m;i++){
		chooseTNode(p,i-1,&s1,&s2);				//choose two minimum weight among 1 to i-1
		p[i].lchild = s1;
		p[i].rchild = s2;
		p[s1].parent = i;
		p[s2].parent = i;
		p[i].weight = p[s1].weight + p[s2].weight;
	}

	//find the code
	*hc = (char **)malloc(sizeof(char *) * (n + 1));
	q = *hc;
	cd = (char *)malloc(sizeof(char) * n);				//store the code
	for(i=1;i<=n;i++){
		start = n - 1;						//the start position in cd
		cd[start] = '\0';
		for(j=i,f=p[j].parent;f!=0;j=f,f=p[j].parent){
			if(p[f].lchild == j){
				cd[--start] = '0';
			}else{
				cd[--start] = '1';
			}
		}
		q[i] = (char *)malloc(sizeof(char) * (n - start));	//allocate space for the ith element
		strcpy(q[i],cd+start);
	}
	free(cd);
}


//find the huffman code
void findHuffmanCode(HuffmanCode *ht,char ***hc,int n){
	int m,p,clen,i;
	char *cd,**q;
	m = 2 * n - 1;
	for(i=1;i<=m;i++){
		ht[i].weight = 0;		//as the flag
	}
	p = m;					//traverse at the root
	clen = 0;
	cd = (char *)malloc(sizeof(char) * n);
	*hc = (char **)malloc(sizeof(char *) * (n + 1));
	q = *hc;
	while(p != 0){
		if(ht[p].weight == 0){		//go left
			ht[p].weight = 1;
			if(ht[p].lchild != 0){
				p = ht[p].lchild;
				cd[clen++] = '0';
			}else if(ht[p].rchild == 0){		//get the leaf node
				cd[clen] = '\0';
				q[p] = (char *)malloc(sizeof(char) * (clen + 1));
				strcpy(q[p],cd);
			}
		}else if(ht[p].weight == 1){			//go right
			ht[p].weight = 2;
			if(ht[p].rchild != 0){
				p = ht[p].rchild;
				cd[clen++] = '1';
			}
		}else{
			ht[p].weight = 0;
			p = ht[p].parent;	//return to parent node
			clen--;
		}
	}
}
