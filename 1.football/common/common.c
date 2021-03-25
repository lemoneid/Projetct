/*************************************************************************
	> File Name: common.c
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 14时31分11秒
 ************************************************************************/

// static extern

#include "head.h"
char conf_ans[512];

char *get_conf_value(const char *path, const char *key) {
    FILE *fp = NULL;
    char *line = NULL, *sub = NULL;
    ssize_t nread = 0, len = 0;
    if (path == NULL || key == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if ((fp = fopen(path, "r")) == NULL) {
        errno = EINVAL;
        return NULL;
    }
    while ((nread = getline(&line, &len, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) {
            continue;
        }
        if (line[strlen(key)] == '=') {
            strncpy(conf_ans, sub + strlen(key) + 1, nread - strlen(key) - 2);
            *(conf_ans + nread - strlen(key) - 2) = '\0';
            break;
        }
    } 
    free(line);
    fclose(fp);
    if (sub == NULL) return NULL;
    return conf_ans;
}

void make_non_block_ioctl(int fd) {
    unsigned long ul = 1;
    ioctl(fd, FIONBIO, &ul);
}

void make_block_ioctl(int fd) {
    unsigned long ul = 0;
    ioctl(fd, FIONBIO, &ul);
}

int make_non_block(int fd) {
    int flag; 
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    //flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag|O_NONBLOCK);
    return 0;
}

int make_block(int fd) {
    int flag; 
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    fcntl(fd, F_SETFL, flag&~O_NONBLOCK);
    return 0;
}
