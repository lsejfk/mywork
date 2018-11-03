#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 4
typedef int LeavesElemType;

struct Leaves_tag{
	int dl;
	int num;
	LeavesElemType data[M];
};

struct Dir_tag{
	int class_tag;
	struct Leaves_tag *son;
};

typedef struct Dir_tag *DT;

DT dt_init(
