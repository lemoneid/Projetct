/*************************************************************************
	> File Name: client_recver.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时17分55秒
 ************************************************************************/

#include "head.h"
#include "game.h"
#include "cJSON.h"
//#include "client_re_drew.h"

extern int sockfd;

void *client_recv(void *arg) {
    while (1) {
        struct FootBallMsg msg;
        struct User user;
        bzero(&msg, sizeof(msg));
        bzero(&user, sizeof(user));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        user.team = msg.team;
        if (msg.type & FT_HEART) {
			DBG(RED"HeartBeat from Server 心跳\n"NONE);
			msg.type = FT_ACK;
			send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if (msg.type & FT_MSG) {
            DBG(GREEN"%s : "NONE"%s\n", user.name, msg.msg);
			Show_Message( , &user, msg.msg, 0);
        } else if (msg.type & FT_WALL) {
			DBG(GREEN"Server Msg: "NONE"%s\n", msg.msg);
			Show_Message( , NULL, msg.msg, 1);
		} else if (msg.type & FT_FIN) {
			DBG(GREEN"Server is going to stop!\n"NONE);
			endwin();
			exit(0);
		} else if (msg.type & FT_MAP) {
			cJSON *root = cJSON_Parse(msg.msg);
			re_drew(root);
		} else if (msg.type & FT_SCORE) {
			cJSON *root = cJSON_Parse(msg.msg);
			char tmp[512] = {0};
			sprintf(tmp, "%s get 1 score", cJSON_GetObjectItem(root, "name")->valuestring);
			Show_Message( , NULL, tmp, 1);
		} else {
			DBG(GREEN"Server Msg :"NONE"Unsupport Message Type.\n");
		}
    }

    return NULL;
}
