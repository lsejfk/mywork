#ifndef MFSET_H
#define MFSET_H
/*
create a MFSet abstract data type
*/
typedef struct MFSetADT *MFSet;	

//initialize the MFSet
void initMFSet(MFSet s);

//find the subset to which s belongs
int find(MFSet s,int elem);

//merge two subset into one set
void merge(MFSet s,int i,int j);
#endif
