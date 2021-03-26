/*************************************************************************
	> File Name: udp_client.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月26日 星期五 21时11分52秒
 ************************************************************************/

#include "head.h"

int socket_udp() {

	int sockfd;
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
	printf("Socket create. \n");
	return sockfd;
}

