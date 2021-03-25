/*************************************************************************
	> File Name: client.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 09:16:27 2021
 ************************************************************************/

#include "../common/head.h"
#include "../common/datatype.h"
#include "../common/udp_socket.h"
#include "../common/game.h"

char server_ip[20] = {0};
int server_port = 0;
char *conf = "./football.conf";
struct Bpoint ball;
struct Map court;
WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
int sockfd;
void logout(int signum);

int main(int argc, char **argv) {
    int opt;
    pthread_t recv_t, draw_t;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    while ((opt = getopt(argc, argv, "h:p:")) != -1) {
        switch (opt) {
            case 'h' :
                strcpy(server_ip, optarg);
                break;
            case 'p' :
                server_port = atoi(optarg);
                break;
            default :
                fprintf(stderr, "Usage : %s [-h host] [-p port]\n", argv[0]);
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);
    if (argc > 1) {
        fprintf(stderr, "---Usage : %s [-h host] [-p port]!\n", argv[0]);
        exit(1);
    }

    if (!server_port) server_port = atoi(get_conf_value(conf, "SERVERPORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_conf_value(conf, "SERVERIP"));
        if (!strlen(request.name)) strcpy(request.name, get_conf_value(conf, "NAME"));
    if (!strlen(request.msg)) strcpy(request.msg, get_conf_value(conf, "LOGMSG"));
    if (!request.team) request.team = atoi(get_conf_value(conf, "TEAM"));
    DBG(GREEN"Name=%s, team=%d, msg=%s, IP=%s, port=%d\n"NONE,request.name, request.team, request.msg ,server_ip, server_port)

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = server_port;
    server.sin_addr.s_addr = inet_addr(server_ip);
    socklen_t len = sizeof(struct sockaddr_in);

    DBG(GREEN"INFO"NONE" : server_ip = %s, server_port = %d, name = %s, team = %s logmsg = %s\n", server_ip, server_port, request.name, (request.team ? "BLUE" : "RED"), request.msg);

    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }
    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    int retval = select(sockfd + 1, &set, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select");
        exit(1);
    } else if (retval == 0) {
        DBG(RED"error:"NONE"out of service");
		exit(1);
    } else {
        int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
		if (ret != sizeof(response) || response.type) {
			DBG(RED"ERROR : "NONE"The Game Server refused your login.\n\tThis May be helpfull: %s\n", response.msg);
			exit(1);
        }
    }
    connect(sockfd, (struct sockaddr *)&server, len);
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
       fclose(stdin);
        while (1) {
            struct FootBallMsg msg;
            ssize_t rsize = recv(sockfd, (void *)&msg, sizeof(msg), 0);
            if (msg.type & FT_HEART) {
                DBG(RED"HeartBeat from Server \n"NONE);
                msg.type = FT_ACK;
                send(sockfd, (void *)&msg, sizeof(msg), 0);
            } else if (msg.type & (FT_MSG | FT_WALL)) {
                DBG(GREEN" Server Msg : "NONE"%s\n", msg.msg); 
            } else {
                DBG(GREEN"Server Msg : "NONE"Unsupport Message Type.\n");
            }
        }
    } else {
        while (1) {
            struct FootBallMsg msg;
            msg.type = FT_MSG;
            DBG(YELLOW"Input Message : "NONE);
            fflush(stdout);
            scanf("%[^\n]s", msg.msg);
            getchar();
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } 
    }
//    pthread_create(&recv_t, NULL, client_recv, NULL);
    return 0;

}


void logout(int signum) {
	struct FootBallMsg msg;
	msg.type = FT_FIN;
	send(sockfd, (void *)&msg, sizeof(msg), 0);
	endwin();
	exit(1);
}

