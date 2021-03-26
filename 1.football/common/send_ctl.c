/*************************************************************************
	> File Name: send_ctl.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时04分08秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern struct FootBallMsg ctl_msg;

void send_ctl() {
	if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry) {
		send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
	}
	ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}
