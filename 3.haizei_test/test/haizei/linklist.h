/*************************************************************************
	> File Name: haizei/linklist.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年06月23日 星期二 15时51分18秒
 ************************************************************************/

#ifndef LINKLIST_H
#define LINKLIST_H

#define offset(T, name) ((long long)(&((T *)(0))->name))
#define Head(p, T, name) ((T*)(((char *)p) - offset(T, name)))

struct LinkNode {
    struct LinkNode *next;
};
#endif
