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
    if (ctl_msg.ctl.dirx | ctl_msg.ctl.diry) {
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
    }
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
    return ;
}

void send_ctl_flag(int flag) {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = flag;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}

void send_ctl_stop() {
    send_ctl_flag(ACTION_STOP);
    return ;
}

void send_ctl_kick() {
    send_ctl_flag(ACTION_KICK);
    return ;
}

void send_ctl_carry() {
    send_ctl_flag(ACTION_CARRY);
    return ;
}
