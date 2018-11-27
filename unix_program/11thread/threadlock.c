#include "apue.h"
#include "myerr.h"
#include <pthread.h>
#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)
static pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;
struct foo {
     int f_count;        //protected by hash lock
     int f_id;
     pthread_mutex_t f_lock;
     struct foo *next;   //protected by hash lock
};

static struct foo *fh[NHASH];

struct foo *foo_alloc(int id){
     struct foo *fp;
     int index;
     fp = (struct foo *)malloc(sizeof(struct foo));
     if(fp == NULL){
          fprintf(stderr,"malloc failed\n");
          exit(1);
     }
     fp->f_count = 1;
     fp->f_id = id;
     if(pthread_mutex_init(&fp->f_lock) != 0){
          free(fp);
          return NULL;
     }
     index = HASH(id);
     pthread_mutex_lock(&hashlock);
     fp->next = fh[index];
     fh[index] = fp;
     pthread_mutex_lock(&fp->f_lock);
     pthread_mutex_unlock(&hashlock);
     //....
     pthread_mutex_unlock(&fp->f_lock);
     return fp;
}

void foo_hold(struct foo *fp){
     pthread_mutex_lock(&hashlock);
     fp->f_count++;
     pthread_mutex_unlock(&hashlock);
}

struct foo *foo_find(int id){
     int index;
     struct foo *fp;
     index = HASH(id);
     pthread_mutex_lock(&hashlock);
     for(fp=fh[index];fp;fp=fp->next){
          if(fp->f_id = id){
               fp->f_count++;
               return fp;
          }
     }
     pthread_mutex_unlock(&hashlock);
     return NULL;
}

void foo_rele(struct foo *fp){
     struct foo *tmp;
     int index;
     pthread_mutex_lock(&hashlock);
     if(--fp->f_count == 0){
          index = HASH(fp->f_id);
          tmp = fh[index];
          if(tmp == fp){
               fh[index] = fp->next;
          }else{
               while(tmp->next != fp){
                    tmp = tmp->next;
               }
               tmp->next = fp->next;
          }
          pthread_mutex_unlock(&hashlock);
          pthread_mutex_destroy(&tmp->f_lock);
          free(tmp);
     }else{
          pthread_mutex_unlock(&hashlock);
     }
}
