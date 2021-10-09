/*************************************************************************
	> File Name: client_re_drew.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时29分53秒
 ************************************************************************/

#ifndef _CLIENT_RE_DREW_H
#define _CLIENT_RE_DREW_H
void re_drew_player(cJSON *users);
void re_drew_ball(cJSON *c_ball);
void re_drew_score(cJSON *c_score);
void ball_door();
void re_drew(cJSON *root);
#endif
