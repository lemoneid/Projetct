/*************************************************************************
	> File Name: server_re_drew.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 21时01分01秒
 ************************************************************************/

#ifndef _SERVER_RE_DREW_H
#define _SERVER_RE_DREW_H
void re_drew_player(int team, char *name, struct Point *loc);
void re_drew_team(struct User *team);
void re_draw_ball();
void init_score();
void re_drew();
#endif
