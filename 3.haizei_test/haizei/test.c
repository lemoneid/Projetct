#include <haizei/test.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <haizei/linklist.h>

struct Function func_head, *func_tail = &func_head;
struct FunctionInfo htest_info;

int RUN_ALL_TESTS() {    
    for (struct LinkNode *p = func_head.p.next; p != NULL; p = p->next) {
        struct Function *func = Head(p, struct Function, p);
        htest_info.success = htest_info.total = 0;
        printf(GREEN_HL("[====RUN====] ")RED_HL("%s\n"), func->str);
        func->func();
        double ans = htest_info.success * 100.0 / htest_info.total;
        printf(GREEN("[ "));
        if (fabs(ans - 100.0) < 1e-6) {
            printf(BLUE_HL("%6.2lf%%"), ans);
        } else {
            printf(RED_HL("%6.2lf%%"), ans);
        }
        printf(
            GREEN(" ]")
            " total : %d success : %d\n\n", 
            htest_info.total, 
            htest_info.success
            );
    }
    return 0;
}

void add_function(TestFuncT func, const char *str) {
    struct Function *temp = (struct Function *)calloc(1, sizeof(struct Function)) ; // calloc可以清空赋值,calloc(节点个数,所占空间)
    temp->func = func;
    temp->str = strdup(str); //将str地址下的字符串拷贝一份
    func_tail->p.next = &(temp->p);
    func_tail = temp;
    return ;
}

