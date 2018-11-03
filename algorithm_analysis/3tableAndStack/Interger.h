#ifndef INTERGER_H
#define INTERGER_H

struct Interger{
	int exp;
	int num;
	struct Interger *next;
};

typedef struct Interger *PtrToIntNode;
typedef PtrToIntNode IntNum;


#endif
