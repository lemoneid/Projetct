/*************************************************************************
	> File Name: common.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 14时31分19秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
void make_non_block_ioctl(int fd);
void make_block_ioctl(int fd);
int make_non_block(int fd);
int make_block(int fd);
char *get_conf_value(const char *path, const char *key);
#endif

