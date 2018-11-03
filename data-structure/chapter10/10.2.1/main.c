#include "straInsertSort.h"

int main(){
	SeqList list;
	inputData(&list);
	printData(&list);
	//insertSort(&list);
	binInsertSort(&list);
	printData(&list);
	return 0;
}
