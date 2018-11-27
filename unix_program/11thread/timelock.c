#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>

int main(){
     struct timespec tout;
     struct tm *tmp;
     int err;
     char buf[64];
     pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

     pthread_mutex_lock(&lock);
     printf("now is locked\n");
     clock_gettime(CLOCK_REALTIME,&tout);
     tmp = localtime(&tout.tv_sec);
     strftime(buf,sizeof(buf),"%F %T",tmp);
     printf("the current time is %s\n",buf);

     tout.tv_sec += 10;
     err = pthread_mutex_timedlock(&lock,&tout);
     clock_gettime(CLOCK_REALTIME,&tout);
     tmp = localtime(&tout.tv_sec);
     strftime(buf,sizeof(buf),"%F %T",tmp);
     printf("now time %s\n",buf);
     if(err != 0){
          printf("can't lock mutex again:%s\n",strerror(err));
     }else{
          printf("locked again\n");
     }
     return 0;
}
