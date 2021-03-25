/*************************************************************************
	> File Name: udp_epoll.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 09:00:31 2021
 ************************************************************************/

#include "./color.h"
#include "./common.h"
#include "./head.h"
#include "./udp_socket.h"
extern int port;
extern struct User *rteam;
extern struct User *bteam;
extern int repollfd, bepollfd;
extern struct Map court;

void add_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    DBG(YELLOW"EPOLL"NONE" : After Epoll Add.\n");
}


void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    DBG(GREEN"Sub Thread"NONE" : After Epoll Add %s.\n", user->name);
}
void del_event(int epollfd, int fd) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);

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

    DBG(GREEN"INFO"NONE" : After connect.\n");
    int ret = send(sockfd, "Login!", sizeof("Login!"), 0);
    DBG(RED"RET = %d\n"NONE, ret);

    return  sockfd;
}

int check_online(struct LogRequest *request) {
	for (int i = 0; i < MAX_USER; i++) {
		if (rteam[i].online && !strcmp(rteam[i].name, request->name)) return 1;
		if (bteam[i].online && !strcmp(bteam[i].name, request->name)) return 1;
	}
	return 0;
}

int udp_accept(int epollfd, int fd, struct User *user) {
    struct sockaddr_in client;
    socklen_t len = sizeof(struct sockaddr_in);
    int new_fd, ret;

    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    len = sizeof(struct sockaddr_in);
    if (ret != sizeof(request)) {
        response.type = 1;
        strcpy(response.msg, "Login failed with NewWork Errors!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    response.type = 0;
    strcpy(response.msg, "Login success, Enjoy youself.");
    sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
    
    if (request.team) {
        DBG(GREEN"INFO"NONE" : "BLUE" %s on %s:%d login! (%s)\n"NONE, request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    } else {
        DBG(GREEN"INFO"NONE" : "RED" %s on %s:%d login! (%s)\n"NONE, request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    }
	strcpy(user->name, request.name);
    /*
	if (request.team == 0) user->loc.x = 2;
	else user->loc.x = court.width - 3;
	user->loc.y = court.height / 2;
    */
	user->team = request.team;
    new_fd = udp_connect(fd, (struct sockaddr *)&client);
    user->fd = new_fd;
    return new_fd;
}

int find_sub(struct User *team) {
    for (int i = 0; i < MAX_USER; i++) {
        if (!team[i].online) return i;
    }
}

void add_to_sub_reactor(struct User *user) {
    struct User *team = (user->team ? bteam : rteam);
   DBG(YELLOW"Main Thread : "NONE"Add to sub_reactor\n");
	int sub = find_sub(team);
	team[sub] = *user; //把user里的数据拷贝一份到team数组中
	team[sub].online = 1;
	team[sub].flag = 10;
	DBG(L_RED"sub = %d, name = %s\n"NONE, sub, team[sub].name);
	if (user->team) {
		add_event_ptr(bepollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
	} else
		add_event_ptr(repollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
}
