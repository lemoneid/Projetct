/*************************************************************************
	> File Name: thread_pool.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 19:27:08 2021
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H
#include "head.h"
#define MAX_N 100
#define MAXXTHREAD 10
struct task_queue {
    int sum;
    int epllfd;
    int head;
    int tail;
    struct User **team;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epolfd);
void task_queue_push(struct task_queue *task_queue, struct User *user);
struct User *task_queue_pop(struct task_queue *taskQueue);
void thread_run(void *arg);

#endif
