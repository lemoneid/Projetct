/*************************************************************************
	> File Name: udp_epoll.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 09:01:17 2021
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

void add_event(int epollfd, int fd, int events);
void del_event(int epollfd, int fd);
int udp_connect(int epollfd, struct sockaddr_in *serveraddr);
int udp_accept(int epollfd, int fd, struct User *user);
void add_to_sub_reactor(struct User *user);
#endif
