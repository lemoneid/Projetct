/*************************************************************************
	> File Name: udp_epoll.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 09:00:31 2021
 ************************************************************************/

#include "./color.h"
#include "./common.h"
#include "./head.h"
void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    DBG(YELLOW"EPOLL"NONE" : After Epoll Add.\n");
}
void del_event(int epollfd, int fd) {
    struct epoll_event ev;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);

}

int udp_connect(int epollfd, struct sockaddr *serveraddr) {
    int sockfd;
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        return -1;
    }
    if (connect(sockfd, (struct sockaddr *)serveraddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return -1;
    }
    add_event(epollfd, sockfd, EPOLLIN);
    return  sockfd;
}

int udp_accept(int fd, struct User *user) {
    struct sockaddr_in client;
    socklen_t len = sizeof(struct sockaddr_in);
    int new_fd, ret;
    ret = recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr *)&client, &len);
    if (ret < 0) {
        return -1;
    }
    new_fd = udp_connect(fd, (struct sockaddr *)&client);
}
void add_to_sub_reactor(struct User *user);
int check_online(struct LogRequest *request);
