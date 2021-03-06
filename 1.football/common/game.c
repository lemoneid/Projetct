/*************************************************************************
	> File Name: game_ui.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com 
	> Created Time: Tue Mar 23 16:13:30 2021
 ************************************************************************/

#include "head.h"

extern struct Map court;
extern WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
int message_num = 0;
WINDOW *create_newwin(int width, int height, int startx, int starty) {
    //Create WINDOW
    WINDOW *win;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);/*0 0是字符默认行列起始位置*/
    wrefresh(win);/*刷新窗口缓冲，显示box*/
    return win;//创建了一个窗口对象
}

void destroy_win(WINDOW *win) {//销毁窗口
    //Destroy WINDOW

    //delete line
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');//删掉线
    wrefresh(win);
    delwin(win);
}


void gotoxy(int x, int y) {
    move(y , x);
}

void gotoxy_putc(int x, int y,char c) {
    move(y, x);
    addch(x);
    move(LINES - 1, 1);
    refresh();
}
void gotoxy_puts(int x, int y,char *c) {
    move(y, x);
    addstr(c);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, char c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void initfootball() {//初始化足球场
    initscr();
    clear();
    if(!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色！\n");
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);    
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);    
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_GREEN);
    init_pair(8, COLOR_BLUE, COLOR_RED);
    init_pair(9, COLOR_BLUE, COLOR_WHITE);
    init_pair(10, COLOR_BLUE, COLOR_YELLOW);
    init_pair(11, COLOR_BLUE, COLOR_CYAN);
    init_pair(12, COLOR_BLUE, COLOR_BLUE);

    Football_t=create_newwin(court.width + 4, court.height + 2, court.start.x - 2, court.start.y - 1);
    Football = subwin(Football_t, court.height, court.width, court.start.y, court.start.x);
    box(Football, 0, 0);
    WINDOW *Message_t=create_newwin(court.width + 4, 7, court.start.x - 2, court.start.y + 1 + court.height);
    Message = subwin(Message_t, 5, court.width + 2, court.start.y + court.height + 2, court.start.x - 1);
    scrollok(Message, 1);
    Help=create_newwin(20, court.height + 2, court.start.x + court.width + 2, court.start.y - 1);
    Score=create_newwin(20,  7, court.start.x + court.width + 2, court.start.y + 2 + court.height - 1);
    Write=create_newwin(court.width + 24, 5, court.start.x - 2, court.start.y + 1 + court.height + 7);
}
void init_help() {
    w_gotoxy_puts(Help, 1, 1, "[wasd]:\n| control direction");
    w_gotoxy_puts(Help, 1, 4, "[ j ]:\n| stop ball");
    w_gotoxy_puts(Help, 1, 7, "[ k ]:\n| kick ball");
    w_gotoxy_puts(Help, 1, 10, "[ l ]:\n| carry ball");
    w_gotoxy_puts(Help, 1, 13, "[space]:\n| choose strength");
    w_gotoxy_puts(Help, 1, 16,"[enter]:\n| send msg");
}


void *draw(void *arg) {
    initfootball();
    init_help();
    while(1) {
        sleep(10);
    }
}


/*在哪个窗口显示信息*/
/*user谁*/
/*msg信息*/
void show_message(WINDOW *win, struct User *user, char *msg, int type) {
    //时间
    time_t time_now = time(NULL);
    struct tm* tm= localtime(&time_now);
    char timestr[20] = {0};
    char username[80] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    
    if (type) {
        //系统信息
        wattron(win, COLOR_PAIR(4));
        strcpy(username, "Server Info : ");
    } else {
        if(user->team) 
            wattron(win, COLOR_PAIR(6));
        else 
            wattron(win, COLOR_PAIR(2));
        sprintf(username, "%s : ", user->name);
    }
    //打印信息
    if(message_num < 4) {
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    } else {
        message_num = 4;
        scroll(win);//滚动
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    }

    wrefresh(win);
}

