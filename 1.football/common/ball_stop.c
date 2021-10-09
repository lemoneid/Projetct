/*************************************************************************
	> File Name: ball_stop.c
	> Author: yanzw
	> Mail: yanzw@pm.me
	> Created Time: 2021年10月09日 星期六 20时50分48秒
 ************************************************************************/

#include "head.h"

extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int ball_stop(struct Point *loc) {
	int px = loc->x;
	int py = loc->y;
	if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		ball_status.a.x = 0;
		ball_status.a.y = 0;
		ball_status.v.x = 0;
		ball_status.v.y = 0;
        return 1;
    }
    return 0;
}


