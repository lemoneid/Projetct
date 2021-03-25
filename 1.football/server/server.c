/*************************************************************************
	> File Name: server.c
	> Author: wei 
	> Mail: 1931248856@qq.com 
	> Created Time: Tue Mar 23 14:59:03 2021
 ************************************************************************/

#include "../common/common.h"
#include "../common/head.h"
#include "../common/color.h"
#include "../common/datatype.h"
#include "../common/game_ui.h"
#include "../common/thread_pool.h"
#include "../common/sub_reactor.c"
#include "../common/udp_epoll.h"

char *conf = "./server.conf";
struct User *rteam;
struct User *bteam;
struct Bpoint ball;
struct BallStatus ball_status;

int repollfd, bepollfd;
int data_port;
int port = 0;


int main(int argc, char **argv) {
    int opt, listener, epoll_fd;

    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p' :
                port = atoi(optarg);
                break;
            default : 
                fprintf(stderr, "Usage %s [-p port]\n", argv[0]);
                exit(1);
        }
    }

    argc -= (optind);
    argv += (optind);

    if (argc > 1) {
        fprintf(stderr, "Usage %s [-p port]\n", argv[0]);
        exit(1);
    }
    
    if (!port) port = atoi(get_conf_value(conf, "PORT"));
    data_port = atoi(get_value(conf, "DATAPORT"));
    court.width = atoi(get_value(conf, "COLS"));
    court.height = atoi(get_value(conf, "LINES"));
    court.start.x = 3;
    court.start.y = 3;
    ball.x = court.width / 2;
	ball.y = court.height / 2;

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));
    
    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_creat_dup");
        exit(1);
    }



    DBG(GREEN"INFO"NONE" : Server start on Port %d\n", port);
#ifndef _D
    //pthread_create(&draw_t, NULL, draw, NULL);
#endif
    epoll_fd = epoll_create(MAX * 2);
    repollfd = epoll_create(MAX);
    bepollfd = epoll_create(MAX);

    if (epoll_fd < 0 || repollfd < 0 || bepollfd < 0) {
        perror("epoll_create");
        exit(1);
    }

    struct task_queue redQueue;
    struct task_queue blueQueue;
    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);
    pthread(&red_t, NULL, sub_reactor, (void *)redQueue);
    Pthread(&blue_t, NULL, sub_reactor, (void *)blueQueue);

    struct epoll_event ev, events[MAX * 2];
    ev.events = EPOLLIN;
    ev.data.fd = listener;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener, &ev);
    struct LogData lg;
    //ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
    struct sockaddr *src_addr, socklen_t *addrlen);
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    //UDP实际只有listener一个文件
    while (1) {
        DBG(YELLOW"Main Pthread"NONE" : before epoll_wait\n");
        int nfds = epoll_wait(epoll_fd, events, MAX * 2, -1);
        DBG(YELLOW"Main Pthread"NONE" : after epoll_wait\n");


        for (int i = 0; i < nfds; i++) {
            struct User user;
            char buff[512] = {0};
            if (events[i].data.fd == listener) {
                //accept
                int new_fd = udp_accept(epoll_fd, listener, &user);
                if (new_fd > 0) {
                    DBG(YELLOW"Main Thread"NONE" : Add %s to %s sub_reactor\n", user.name, (user.team ? "BLUE" : "RED"));
                }

            }
        }
    }

    return 0;
}
