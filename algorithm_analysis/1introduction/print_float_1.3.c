#include <stdio.h>
#include <stdlib.h>
/*
Note: 
a = 2.345;
b = (int)a;
c = a - b;	c=0.344999999
so we need to add 0.0001
*/

#define printDigit(ch) (putchar((ch) + '0'));

void printInt(long n){
	if(n >= 10){
		printInt(n / 10);
	}
	printDigit(n % 10);
}

void printOut(double di,int acc){
	long intdi;
	double decimal,add;
	int i;
	add = 0.1;
	if(di < 0){
		putchar('-');
		di = (-1) * di;
	}
	intdi = (long)di;
	decimal = di - intdi;
	printInt(intdi);
	putchar('.');
	for(i=0;i<acc;i++){
		add /= 10;
	}
	decimal += add;
	for(i=0;i<acc;i++){
		decimal *= 10;
	}
	intdi = (long)decimal;
	printInt(intdi);
}

int main(int argc,char *argv[]){
	if(argc != 3){
		fprintf(stderr,"usage:a.out <digit> <accurency>\n");
		return -1;
	}
	printOut(atof(argv[1]),atoi(argv[2]));
	putchar('\n');
	return 0;
}
