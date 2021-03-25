/*************************************************************************
	> File Name: heart_beat.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 14时26分51秒
 ************************************************************************/

#include "head.h"
#include "datatype.h"
#include "udp_epoll.h"
#include "game.h"
extern struct User *rteam, *bteam;
extern int repollfd, bepollfd;

void heart_beat_team(struct User *team) {
    struct FootBallMsg msg;
    msg.type = FT_HEART;
    for (int i = 0; i < MAX_USER; i++) {
        if (!team[i].online) continue;
        if (!team[i].flag) {
            team[i].online = 0;
            continue;
        }
        send(team[i].fd, (void *)&msg, sizeof(msg), 0);
        team[i].flag--;
        if (team[i].flag <= 0) {
            char buff[512] = {0};
            sprintf(buff, "%s is removed from list.", team[i].name);
            team[i].online = 0;
            int epollfd_tmp = (team[i].team ? bepollfd : repollfd);
            del_event(epollfd_tmp, team[i].fd);
        }
    }
    return ;
}

void *heart_beat(void *arg) {
    while (1) {
        sleep(10);
        heart_beat_team(bteam);
        heart_beat_team(rteam);
    }
}