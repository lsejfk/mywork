#include "linklist.h"
#include <stdio.h>

int main(){
	struct LinkList myList;
	ElemType n;
	init_link_list(&myList);
	printf("Please input list data seperated by space:\n");
	while((scanf("%d",&n) != EOF)){
		insert_into_list(&myList,n);
	}
	printf("The list is:");
	link_list_print(&myList);
	return 0;
}
