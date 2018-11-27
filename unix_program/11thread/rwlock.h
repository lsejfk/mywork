#ifndef RWLOCK_H
#define RWLOCK_H
#include <pthread.h>
struct job;
struct jobQueue;

//initialize a queue
int queue_init(struct jobQueue *qp);
//insert a job at the head of the queue
void job_insert(struct jobQueue *qp,struct job *jp);
//append a job on the tail of the queue
void job_append(struct jobQueue *qp,struct job *jp);
//remove a give job from a queue
void job_remove(struct jobQueue *qp,struct job *jp);
//find a job for the given thread id
struct job *job_find(struct jobQueue *qp,pthread_t tid);
//create a new job
struct job *job_create(pthread_t tid);
struct job *job_next(struct jobQueue *qp);

#endif
