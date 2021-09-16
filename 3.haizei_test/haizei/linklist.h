/*************************************************************************
	> File Name: linklist.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年06月18日 星期四 19时45分17秒
 ************************************************************************/

#ifndef _LINKLIST_H
#define _LINKLIST_H

#define offset(T, name) (long long)(&((T *)(0))->name)

#define Head(p, T, name) ((T *)(((char *)p) - offset(T, name)))

//offset() T结构体name字段的地址偏移量
//
//
//Head() 节点的next地址,当前结构体类型,下一节点的name字段;

struct LinkNode {
    struct LinkNode *next;
};

#endif
