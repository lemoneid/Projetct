/*************************************************************************
	> File Name: send_chat.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 20时01分07秒
 ************************************************************************/

#include "head.h"
#include "game.h"

extern int sockfd;
extern WINDOW *Write;
extern struct FootBallMsg chat_msg;

void send_chat() {
    echo();
    nocbreak();
    bzero(&chat_msg.msg, sizeof(chat_msg.msg));
    w_gotoxy_puts(Write, 1, 1, "Input Message:");
    mvwscanw(Write, 2, 1, "%[^\n]s", chat_msg.msg);
    if (strlen(chat_msg.msg)) {
        send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
    }
    werase(Write);
    box(Write, 0, 0);
    wrefresh(Write);
    noecho();
    cbreak();
    return;
}
