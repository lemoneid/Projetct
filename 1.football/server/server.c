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

char *conf = "./server.conf";
struct User *rteam;
struct User *bteam;
struct Bpoint ball;
struct BallStatus ball_status;

int repollfd, bepollfd;
int data_port;
//int port = 0;


int main(int argc, char **argv) {
    int opt, port = 0, listener;

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
    court.start.x = 1;
    court.start.y = 1;
    ball.x = court.width / 2;
	ball.y = court.height / 2;

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));
    
    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_creat_dup");
        exit(1);
    }



    DBG(GREEN"INFO"NONE" : Server start on Port %d\n", port);

    pthread_create(&draw_t, NULL, draw, NULL);

    epoll_fd = epoll_create(MAX * 2);

    if (epoll_fd < 0) {
        perror("epoll_create");
        exit(1);
    }

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
            char info[1024] = {0};
            if (events.data.fd == listener) {
            }
        }

        recvfrom(listener, (void *)&lg, sizeof(lg), 0, (struct sockadrr *)&client, &len);
        mvwprintw(Message, 0, 0, "Login : %s : %d", inet_ntoa(client.sin_addr), client.sin_port);
    }


    return 0;
}
