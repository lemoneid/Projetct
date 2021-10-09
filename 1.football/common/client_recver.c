/*************************************************************************
	> File Name: client_recver.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时17分55秒
 ************************************************************************/
#include "head.h"
#include "common.h"
#include "client_re_drew.h"

extern int sockfd;

void *client_recv(void *arg) {
    while(1) {
        struct FootBallMsg msg;
        bzero(&msg, sizeof(msg));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        if(msg.type & FT_TEST) {
            DBG(RED"HeartBeat from Server 心\n"NONE);
            msg.type = FT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if(msg.type & (FT_MSG | FT_WALL)) {
            DBG(GREEN"Server Msg : "NONE"%s\n", msg.msg);
        } else if(msg.type & FT_FIN){
            DBG(GREEN"Server is going to stop.\n"NONE);
            endwin();
            exit(0);
        } else if (msg.type & FT_GAME) {//服务端向客户端广播的json实时地图
			DBG(YELLOW"JSON:"NONE"%s", msg.msg);
			cJSON *root = cJSON_Parse(msg.msg);
			re_drew(root);
		} else {
            DBG(GREEN"Msg Unsupport\n"NONE);
            exit(0);
        }
        
    }
}
/*
{
	"name":	"test",
	"ball":	{
		"x":	57,
		"y":	12
	},
	"score":	{
		"bscore":	0,
		"rscore":	0
	},
	"users":	[{
			"team":	0,
			"name":	"ZFB",
			"locx":	2,
			"locy":	12
		}]
}
*/
