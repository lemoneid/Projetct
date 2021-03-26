/*************************************************************************
	> File Name: head.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年07月26日 星期日 18时37分15秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

//football
#include "color.h"
#include "common.h"
#include "datatype.h"
#include "cJSON.h"
//
#include <ncurses.h>
#include <locale.h>

//system
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <semaphore.h>
#include <sys/select.h>
#include <sys/time.h>

#ifdef _D
#define DBG(fmt, args...); printf(fmt, ##args);
#else
#define DBG(fmt, args...);
#endif

#endif
