#ifndef SEQUENTIALTABLE_H
#define SEQUENTIALTABLE_H
typedef int SSTDataType;
typedef struct {
	SSTDataType data;
	double weight;
}SSTElemType;
typedef struct {
	SSTElemType *elem;	//the base address for storage of data,allocated in real length
	int length;		//the table length
}SSTable;


void createSequentialtable(SSTable *tab);
#endif
