/*************************************************************************
	> File Name: game_ui.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Tue Mar 23 16:13:35 2021
 ************************************************************************/

#ifndef _GAME_UI_H
#define _GAME_UI_H


#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)
#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, Message),DEFARG(arg1, NULL), arg2, DEFARG(arg3, 0))

#define MAX 50

struct Map court;/*球场*/


WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
WINDOW *create_newwin(int width, int height, int startx, int starty);/*创建一个窗口*/

void destroy_win(WINDOW *win);//销毁一个窗口
void gotoxy(int x, int y);//移动打印光标
void gotoxy_putc(int x, int y, char c);//打印字符
void gotoxy_puts(int x, int y, char *s);//打印字符串
void w_gotoxy_putc(WINDOW *win, int x, int y, char c);//在窗口上打印字符
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);//在窗口上打印字符串
void initfootball();//初始化整个足球场
void init_help();//初始化帮助信息
void *draw(void *arg);//绘制图

void show_message(WINDOW *win, struct User *user, char *msg, int type);//展示消息

#endif
