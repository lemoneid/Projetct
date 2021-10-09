/*************************************************************************
	> File Name: common.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 14时31分19秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
char *get_value(char *path, char *key);
void make_nonblock_ioctl(int fd);
void make_block_ioctl(int fd);
void make_nonblock(int fd);
void make_block(int fd);

#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

#endif

