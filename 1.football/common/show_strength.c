/*************************************************************************
	> File Name: show_strength.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 20时45分23秒
 ************************************************************************/

#include "head.h"

//在Write窗口中，显示踢球力度条，光标在进度条上快速移动
//设置0文件为非阻塞IO
//while 等待空格或者'k'键的按下，如果按下退出，取得当前的strength
//通过sockfd向服务端发送控制信息，踢球
extern WINDOW *Write;
extern int sockfd;
extern struct Map court;
int strength = 1;

void set_ball(int flag, int strength) {
	struct FootBallMsg msg;
	msg.type = FT_CTL;
	msg.ctl.action = flag;
	msg.ctl.strength = strength;
	send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}

void stop_ball() {
    set_ball(ACTION_STOP, 0); 
    return ;
}

void kick_ball() {
    set_ball(ACTION_KICK, strength);
    return ;
}

void carry_ball() {
    set_ball(ACTION_CARRY, 0);
    return ;
}

void show_strength() {
    int maxx, maxy, loc = 2, dir = 1;
	int arr[5] = {1, 2, 3, 2, 1};
	getmaxyx(Write, maxy, maxx);
	for (int i = 2; i < maxx - 2; i++) {
		if (i < maxx / 5 || i > 4 * maxx / 5) {
			wattron(Write, COLOR_PAIR(7));
		} else if (i < 2 * (maxx / 5) || i > 3 * (maxx / 5)) {
			wattron(Write, COLOR_PAIR(9));
		} else {
			wattron(Write, COLOR_PAIR(8));
		}
		mvwprintw(Write, 2, i, " ");
	}
	wrefresh(Write);
	make_non_block(0);
	while (1) {
		char c = getchar();
		if ( c != -1) {
			if (c == ' ' || c == 'k') {
				//arr[loc / 5]
				struct FootBallMsg msg;
				msg.type = FT_CTL;
				msg.ctl.action = ACTION_KICK;
				strength = msg.ctl.strength = arr[loc / (maxx / 5)];
				send(sockfd, (void *)&msg, sizeof(msg), 0);
				for (int i = 0; i <= court.width; i++) {
					mvwprintw(Write, 1, i, " ");
					mvwprintw(Write, 3, i, " ");
				}
				make_block(0);
				break;
			}
		} 
		usleep(30000);
		if (loc >= maxx - 2) dir = -1;
		if (loc <= 2) dir = 1;
		wattron(Write, COLOR_PAIR(3));
		mvwprintw(Write, 1, loc, " ");
		mvwprintw(Write, 3, loc, " ");
		loc += dir;
		mvwprintw(Write, 1, loc, "|");
		mvwprintw(Write, 3, loc, "|");
		mvwprintw(Write, 4, maxx, " ");
		wrefresh(Write);
	}
}
