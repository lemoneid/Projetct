/*************************************************************************
	> File Name: client_re_drew.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时30分06秒
 ************************************************************************/

#include "head.h"
#include "game.h"

#define MAX 50
extern WINDOW *Football, *Football_t, *Score;
extern struct Bpoint ball;
extern struct Score score;

void re_drew_player(cJSON *users) {
    int user_cnt = cJSON_GetArraySize(users);
	for (int i = 0; i < user_cnt; i++) {
		cJSON *user = cJSON_GetArrayItem(users, i);
		int team = cJSON_GetObjectItem(user, "team")->valueint;
		int locx = cJSON_GetObjectItem(user, "locx")->valueint;
		int locy = cJSON_GetObjectItem(user, "locy")->valueint;
		char p = 'K';
        if(team) {
            wattron(Football, COLOR_PAIR(6));
        } else {
            wattron(Football, COLOR_PAIR(2));
        }
        w_gotoxy_putc(Football, locx, locy, p);
        w_gotoxy_puts(Football, locx + 1, locy - 1, cJSON_GetObjectItem(user, "name")->valuestring);
    }
}

void re_drew_ball(cJSON *c_ball) {
	int ballx = cJSON_GetObjectItem(c_ball, "x")->valueint;
	int bally = cJSON_GetObjectItem(c_ball, "y")->valueint;
	w_gotoxy_putc(Football, ballx, bally, 'o');
}

void re_drew_score(cJSON *c_score) {

    score.blue = cJSON_GetObjectItem(c_score, "bscore")->valueint;
	score.red = cJSON_GetObjectItem(c_score, "rscore")->valueint;
    
    w_gotoxy_puts(Score, 1, 1, "red blue\n");
    char tmp[50];
    sprintf(tmp, "%d:%d", score.red, score.blue);
    w_gotoxy_puts(Score, 1, 2, tmp);
}

void ball_door(){
    for(int i = court.height / 2 - 4; i <= court.height / 2 + 4; i++){
        w_gotoxy_putc(Football_t, 1, i, 'x');
        w_gotoxy_putc(Football_t, 117, i, 'x');
    }
}

void re_drew(cJSON *root) {
	cJSON *users = cJSON_GetObjectItem(root, "users");
	cJSON *c_ball = cJSON_GetObjectItem(root, "ball");
	cJSON *c_score = cJSON_GetObjectItem(root, "score");

    werase(Football);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    re_drew_player(users);
    re_drew_ball(c_ball);
    re_drew_score(c_score);
    ball_door();
    wrefresh(Football);
    wrefresh(Football_t);
}

