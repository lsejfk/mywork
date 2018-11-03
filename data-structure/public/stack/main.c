#include "MultLinkStack.h"

int main(){
	int e;
	double c;
	MultLinkStack st,at;
	initMultLinkStack(&st,sizeof(int));
	initMultLinkStack(&at,sizeof(double));
	printf("st :\n");
	e = 45;
	push(&st,&e);
	e = 34;
	push(&st,&e);
	printf("the first:%4d",(*((int *)pop(&st))));
	printf("get top:%4d",(*((int *)getTop(&st))));
	printf("the second:%4d",(*((int *)pop(&st))));
	printf("\nat:\n");
	c = 1658.213;
	push(&at,&c);
	c = 4987.629;
	push(&at,&c);
	printf("the first :%f\n",(*((double *)pop(&at))));
	printf("get top:%f\n",(*((double *)getTop(&at))));
	printf("the second :%f\n",(*((double *)pop(&at))));

	return 0;
}
