#include "rwlock.h"
#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_POOL_NUM 3
typedef void *(*Process_fun)(void *);
Process_fun process_msg[THREAD_POOL_NUM];
struct job *msg;
struct jobQueue qp;
pthread_cond_t qready[THREAD_POOL_NUM];
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void *process_msg0(void *arg){
     struct job *jp;
     while(1){
          pthread_mutex_lock(&qlock);
          while(msg == NULL){
               pthread_cond_wait(&qready[0],&qlock);
          }
          jp = msg;
          pthread_mutex_unlock(&qlock);
     }
}

int main(){
     pthread_t tid[THREAD_POOL_NUM];
     int i,id,num;
     struct job *p;
     for(i=0;i<THREAD_POOL_NUM;i++){
          pthread_cond_init(&qready[i],NULL);
     }
     err = queue_init(&qp);
     if(err != 0){
          err_sys("queue initialize failed");
     }
     process_msg[0] = process_msg0;
     process_msg[1] = process_msg1;
     process_msg[2] = process_msg2;
     //create threads
     for(i=0;i<THREAD_POOL_NUM;i++){
          err = pthread_create(&tid[i],NULL,process_msg[i],NULL);
          if(err != 0){
               err_sys("can't create pthread\n");
          }
     }

     while(1){
          //create jobs
          scanf("%d",&num);
          printf("input the process thread id:>");
          while(num-- == 0){
               scanf("%d",&id);
               p = job_create(tid[id]);
               job_insert(&qp,p);
          }
          for(p=job_next(&qp);p != NULL;){
               pthread_mutex_lock(&qlock);
               msg = p;
          }
     }

     
}
