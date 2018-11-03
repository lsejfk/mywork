#include "apue.h"
#include "myerr.h"
#include <pwd.h>
#include <shadow.h>
#include <unistd.h>

int main(){
	struct spwd *ptr;
	setspent();	//self-defence
	while((ptr = getspent())){
		printf("username:%s\npw:%s\ndays last change:%d\ndays until change allowed:%d\ndays before change required:%d\n	days warning for expiration:%d\ndays before account inactive:%d\n",
			ptr->sp_namp,ptr->sp_pwdp,ptr->sp_lstchg,ptr->sp_min,ptr->sp_max,ptr->sp_warn,ptr->sp_inact);
		printf("\n");
	}
	endspent();
	return 0;
}
