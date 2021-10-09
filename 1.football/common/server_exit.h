/*************************************************************************
	> File Name: server_exit.h
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 20时52分13秒
 ************************************************************************/

#ifndef _SERVER_EXIT_H
#define _SERVER_EXIT_H

cJSON *game_msg();
void server_send();
void server_exit(int signum);

#endif
