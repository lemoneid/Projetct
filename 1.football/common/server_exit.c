/*************************************************************************
	> File Name: server_exit.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 20时52分23秒
 ************************************************************************/

#include "head.h"
#define MAX 50
extern struct User *rteam, *bteam;

extern struct Bpoint ball;
extern struct Score score;

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
	"users":	[]
	}

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
			"name":	"FS",
			"locx":	2,
			"locy":	12
		}]
	}
*/
cJSON *game_msg() {//游戏地图打包
	cJSON *root = cJSON_CreateObject();
	cJSON *c_ball = cJSON_CreateObject();//球的对象
	cJSON *users = cJSON_CreateArray();//users数组
	cJSON *c_score = cJSON_CreateObject();//分数对象

	cJSON_AddItemToObject(root, "name", cJSON_CreateString("test"));
	cJSON_AddItemToObject(root, "ball", c_ball);
	cJSON_AddItemToObject(root, "score", c_score);
	cJSON_AddItemToObject(root, "users", users);

	cJSON_AddNumberToObject(c_ball, "x", ball.x);
	cJSON_AddNumberToObject(c_ball, "y", ball.y);

	cJSON_AddNumberToObject(c_score, "bscore", score.blue);
	cJSON_AddNumberToObject(c_score, "rscore", score.red);

	for (int i = 0; i < MAX; i++) {
		if (rteam[i].online) {
			cJSON *user = cJSON_CreateObject();
			cJSON_AddNumberToObject(user, "team", rteam[i].team);
			cJSON_AddStringToObject(user, "name", rteam[i].name);
			cJSON_AddNumberToObject(user, "locx", rteam[i].loc.x);
			cJSON_AddNumberToObject(user, "locy", rteam[i].loc.y);
			cJSON_AddItemToArray(users, user);
		}
		if (bteam[i].online) {
			cJSON *user = cJSON_CreateObject();
			cJSON_AddNumberToObject(user, "team", bteam[i].team);
			cJSON_AddStringToObject(user, "name", bteam[i].name);
			cJSON_AddNumberToObject(user, "locx", bteam[i].loc.x);
			cJSON_AddNumberToObject(user, "locy", bteam[i].loc.y);
			cJSON_AddItemToArray(users, user);
		}
	}
	return root;
}

void server_send() {
	struct FootBallMsg msg;
	msg.type = FT_GAME;
	for (int i = 0; i < MAX; i++) {//发送给所有在线的客户
		if (rteam[i].online) {
			strcpy(msg.msg, cJSON_Print(game_msg()));
			send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
		}
		if (bteam[i].online) {
			strcpy(msg.msg, cJSON_Print(game_msg()));
			send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
		}
	}
}

void server_exit(int signum) {
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    for(int i = 0; i < MAX; i++) {
        if(rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        if(bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
    }
    endwin();
    DBG(RED"Server stopped!\n"NONE);
    exit(0);
}
