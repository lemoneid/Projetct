/*************************************************************************
	> File Name: client.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Wed Mar 24 09:16:27 2021
 ************************************************************************/

#include "../common/head.h"

char server_ip[20] = {0};
int server_port = 0;
char *conf = "./football.conf";

int main(int argc, char **argv) {
    int opt;
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
    if (!strlen(server_ip)) server_ip = strcpy(server_ip, get_conf_value(conf, "SERVERIP"));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = server_port;
    server.sin_addr.s_addr = inet_addr(server_ip);
    socklen_t len = sizeof(struct sockaddr_in);

    DBG(GREEN"INFO"NONE" : server_ip = %s, server_port = %d, name = %s, team = %s logmsg = %s\n", server_ip, server_port, request.name, (request.team ? "BLUE" : "RED"), request.msg);


    return 0;
}
