/*************************************************************************
	> File Name: server.c
	> Author: wei 
	> Mail: 1931248856@qq.com 
	> Created Time: Tue Mar 23 14:59:03 2021
 ************************************************************************/

#include "../common/common.h"
#include "../common/head.h"
#include "../common/color.h"

int main() {
    
    if ((listener = socket_creat_dup(port)) < 0) {
        perror("socket_creat_dup");
        exit(1);
    }

    DBG(GREEN"INFO"NONE" : Server start on Port %d\n", port);
    pthread_create(&draw_t, NULL, NULL);

    return 0;
}
