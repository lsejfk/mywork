#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	ArrQueue Q;
	Q = arrque_createQueue(20);
	arrque_enqueue(1,Q);
	arrque_enqueue(2,Q);
	arrque_enqueue(3,Q);
	arrque_enqueue(4,Q);
	printf("the front:%d\n",arrque_front(Q));
	arrque_dequeue(Q);
	printf("after dequeue:%d\n",arrque_frontAndDequeue(Q));
	arrque_makeEmpty(Q);
	printf("after make empty:%d\n",arrque_frontAndDequeue(Q));
	return 0;
}
