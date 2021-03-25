/*************************************************************************
	> File Name: send_chat.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 20时01分07秒
 ************************************************************************/

#include "head.h"
#include "game.h"

//此函数在按下回车键后调用
extern int sockfd;
extern WINDOW *Write;
extern struct FootBallMsg chat_msg; //外部全局变量
    //打开echo回显
    //打开行缓冲
    //在Write窗口中输入数据并读入
    //判断读入信息非空，发送
    //重绘Write
    //关闭echo
void send_chat() {
    echo();
    nocbreak();
    bzero(chat_msg.msg, sizeof(struct FootBallMsg));
    w_gotoxy_puts(Write, 1, 1, "Input Message : ");
    mvwscanw(Write, 2, 1, "%[^\n]s", chat_msg.msg);
    if (strlen(chat_msg.msg)) {
        send(sockfd, (void *)&chat_msg, sizeof(struct FootBallMsg), 0);
    }
    wclear(Write);
    box(Write, 0, 0);
    wrefresh(Write);
    noecho();
    cbreak();
}


