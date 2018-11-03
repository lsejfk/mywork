#include "SequentialTable.h"
#include<stdio.h>

//initialize the Sequential Table
void createSequentialtable(SSTable *tab){
	int n;
	scanf("%d",&n);
	tab->length = n;
	tab->elem = (SSTElemType *)malloc(sizeof(SSTElemType) * (n + 1));
	assert(tab->elem != NULL);
	for(i=1;i<=n;i++){
		scanf("%d%f",&data,&weight);
		tab->elem[i].data = data;
		tab->elem[i].weight = weight;
	}
}
