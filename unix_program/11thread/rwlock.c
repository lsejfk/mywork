#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "apue.h"
#include "myerr.h"

struct job {
     struct job *j_next; //protected by jq_lock
     struct job *j_prev; //protected by jq_lock
     pthread_t j_id;     //protected by j_lock
     int count;          //protected by jq_lock
     pthread_rwlock_t j_lock;
};

struct jobQueue{
     struct job *jq_head;     //protected by jq_lock
     struct job *jq_tail;     //protected by jq_lock
     pthread_rwlock_t jq_lock;
};

int queue_init(struct jobQueue *qp){
     int err;
     qp->jq_head = qp->jq_tail = NULL;
     err = pthread_rwlock_init(&qp->jq_lock,NULL);
     if(err != 0){
          err_sys("initialize the rwlock failed\n");
     }
     return 0;
}

struct job *job_create(pthread_t tid){
     struct job *jp;
     jp = (struct job *)malloc(sizeof(struct job));
     if(jp == NULL){
          err_sys("job_create:malloc failed");
     }
     jp->j_next = jp->j_prev = NULL;
     jp->j_id = tid;
     jp->count = 1;
     err = pthread_rwlock_init(&jp->j_lock,NULL);
     if(err != 0){
          err_sys("job_create:pthread_mutex_init failed");
     }
     return jp;
}

void job_insert(struct jobQueue *qp,struct job *jp){
     pthread_rwlock_wrlock(&qp->jq_lock);
     if(qp->jq_head == NULL){
          qp->jq_head = jp;
          qp->jq_tail = jp;
     }else{
          jp->j_next = qp->jq_head;
          jp->j_prev = NULL;
          qp->jq_head->j_prev = jp;
          qp->jq_head = jp;
     }
     pthread_rwlock_unlock(&qp->jq_lock);
}

void job_append(struct jobQueue *qp,struct job *jp){
     pthread_rwlock_wrlock(&qp->jq_lock);
     if(qp->jq_tail == NULL){
          qp->jq_head = qp->jq_tail = jp;
     }else{
          jp->j_prev = qp->jq_tail;
          qp->tail->j_next = jp;
          jp->j_next = NULL;
          qp->tail = jp;
     }
     pthread_rwlock_unlock(&qp->jq_lock);
}

void job_remove(struct jobQueue *qp,struct job *jp){
     pthread_rwlock_wrlock(&qp->jq_lock);
     if(--jp->count == 0){
          if(qp->jq_head == jp){
               qp->jq_head = jp->j_next;
               qp->jq_head->j_prev = NULL;
          }else if(qp->jq_tail == jp){
               qp->jq_tail == jp->j_prev;
               qp->jq_tail->next = NULL;
          }else{
               jp->j_prev->next = jp->j_next;
               jp->j_next->j_prev = jp->j_prev;
          }
          pthread_rwlock_unlock(&qp->jq_lock);
          pthread_rwlock_destroy(&jp->j_lock);
          free(jp);
     }else{
          pthread_rwlock_unlock(&qp->jq_lock);
     }
}

struct job *job_find(struct jobQueue *qp,pthread_t tid){
     struct job *p;
     int flag = 0;
     pthread_rwlock_rdlock(&qp->jq_lock);
     for(p=qp->jq_head;p;p=p->j_next){
          pthread_rwlock_rdlock(&p->j_lock);
          if(pthread_equal(tid,p->j_id)){
               pthread_rwlock_unlock(&qp->jq_lock);
               pthread_rwlock_unlock(&p->j_lock);
               pthread_rwlock_wrlock(&qp->jq_lock);
               pthread_rwlock_rdlock(&p->j_lock);
               if(pthread_equal(tid,p->j_id)){
                    p->count++;
                    pthread_rwlock_unlock(&qp->jq_lock);
                    pthread_rwlock_unlock(&p->j_lock);
                    break;
               }else{
                    flag = 1;
                    pthread_rwlock_unlock(&qp->jq_lock);
                    pthread_rwlock_unlock(&p->j_lock);
               }
          }
          pthread_rwlock_unlock(&p->j_lock);
     }
     if(p == NULL && flag == 0){
          pthread_rwlock_unlock(&qp->jq_lock);
     }
     return p;
}

struct job *job_next(struct jobQueue *qp){
     struct job *p;
     pthread_rwlock_wrlock(&qp->jq_lock);
     if(qp->jq_head == NULL){
          pthread_rwlock_unlock(&qp->jq_lock);
          return NULL;
     }
     p = qp->jq_head;
     pthread_rwlock_unlock(&qp->jq_lock);
     return p;
}









