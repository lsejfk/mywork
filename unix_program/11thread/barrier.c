#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

#define NTHR 8
#define NUMNUM 8000000L
#define TNUM (NUMNUM/NTHR)

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

//extern int heapsort(void *,size_t,size_t,int (*)(const void *a,const void *b));

int comp(const void *a,const void *b){
     long la,lb;
     la = *((long *)a);
     lb = *((long *)b);
     if(la == lb){
          return 0;
     }else if(la < lb){
          return -1;
     }else{
          return 1;
     }
}

void *pthr_fn(void *arg){
     long idx = (long)arg;
     //heapsort(&nums[idx],TNUM,sizeof(long),comp);
     qsort(&nums[idx],TNUM,sizeof(long),comp);
     pthread_barrier_wait(&b);
     return (void *)0;
}

void merge(){
     long idx[NTHR];
     long i,minidx,sidx,num;
     for(i=0;i<NTHR;i++){
          idx[i] = i * TNUM;
     }

     for(sidx=0;sidx<NUMNUM;sidx++){
          num = LONG_MAX;
          for(i=0;i<NTHR;i++){
               if((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)){
                    num = nums[idx[i]];
                    minidx = i;
               }
          }
          snums[sidx] = nums[idx[minidx]];
          idx[minidx]++;
     }
}

int main(){
     unsigned long i;
     struct timeval startval,endval;
     int err;
     long long startusec,endusec;
     //pthread_t tid;
     double elapsed;
     
     srandom(1);
     for(i=0;i<NUMNUM;i++){
          nums[i] = random();
     }

     gettimeofday(&startval,NULL);
     //err = pthread_barrier_init(&b,NULL,NTHR+1);
     /*
     if(err != 0){
          err_sys("initialize barrier failed\n");
     }
     */

     for(i=0;i<NTHR;i++){
          /*
          err = pthread_create(&tid,NULL,pthr_fn,(void *)(i*TNUM));
          if(err != 0){
               err_sys("can't create thread\n");
          }
          */
          qsort(&nums[i*TNUM],TNUM,sizeof(long),comp);
     }
    // pthread_barrier_wait(&b);
     merge();
     gettimeofday(&endval,NULL);
     startusec = startval.tv_sec * 1000000 + startval.tv_usec;
     endusec = endval.tv_sec * 1000000 + endval.tv_usec;
     elapsed = ((double)(endusec - startusec) / 1000000.0);
     printf("sort took %.4f seconds\n",elapsed);
     /*
     for(i=0;i<NUMNUM;i++){
          printf("%ld\n",snums[i]);
     }
     */

     return 0;
}

