/*************************************************************************
	> File Name: thread_pool.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 19:29:58 2021
 ************************************************************************/

#include "thread_pool.h"

void do_echo(struct User *user) {
    struct FootBallMsg msg;
    int size = recv(user->fd, (void *)&msg, sizeof(msg), 0);
    if (msg.type & FT_ACK) {

    }
}

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd) {
    taskQueue->sum = sum;
    taskQueue->epollfd = epollfd;
    taskQueue->team = calloc(sum, sizeof(void *));
    taskQueue->head = taskQueue->tail = 0;
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
}

void task_queue_push(struct task_queue *taskQueue, struct User *user) {
    pthread_mutex_lock(&taskQueue->mutex);
    taskQueue->team[taskQueue->tail++] = user;

}

struct User *task_queue_pop(struct task_queue *taskQueue) {

}

void thread_run(void *arg) {
    pthread_t tid = pthread_self();
    pthread_detach(tid);
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while (1) {
        struct User *user = task_queue_pop(taskQueue);
    }
}


