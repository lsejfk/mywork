#include "apue.h"
#include <unistd.h>

int main(){
	printf("the login user is %s\n",getlogin());
	return 0;
}
