/*************************************************************************
	> File Name: sub_reactor.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月24日 星期三 22时08分05秒
 ************************************************************************/

#include "head.h"
#include "thread_pool.h"
#include "sub_reactor.h"

void *sub_reactor(void *arg) {
    struct task_queue *taskQueue = (struct task_queue *)arg;
    pthread_t *tid = (pthread_t *)calloc(MAX_THREAD, sizeof(pthread_t));
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)taskQueue);
    }
    struct epoll_event events[MAX_USER];
    int nfds;
    while (1) {
        DBG(RED"Sub Reactor : "NONE"Epoll waiting...\n");
        nfds  = epoll_wait(taskQueue->epollfd, events, MAX_USER, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            struct User *user = (struct User *)events[i].data.ptr;
            DBG(L_YELLOW"events[n].data.ptr->name = %s\n"NONE, user->name);
            if (events[i].events & EPOLLIN) {
                task_queue_push(taskQueue, user);
            }
        }
    }
    return NULL;
}
