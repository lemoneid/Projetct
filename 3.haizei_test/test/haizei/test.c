/*************************************************************************
	> File Name: test.c
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年06月23日 星期二 09时57分10秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <haizei/test.h>
#include <haizei/linklist.h>
struct Function func_head, *func_tail = &func_head;

int function_cnt = 0;
struct FunctionInfo test_info;

int RUN_ALL_TESTS() {
    for (struct LinkNode *p = func_head.pointer.next; p != NULL; p = p->next) {
        struct Function *func = Head(p, struct Function, pointer);
        test_info.total = test_info.success = 0;
        printf(GREEN_HL("[====RUN====]") YELLOW_HL(" %s\n"), func->str);
        func->func();
        double rate = 100.0 * test_info.success / test_info.total;
        printf(GREEN("[  "));
        if (fabs(rate - 100) < 1e-6) {
            printf(BLUE_HL("%6.2lf%%"), rate);
        } else {
            printf(RED_HL("%6.2lf%%"), rate);
        }
        printf(GREEN("  ]") 
            " total : %d success : %d\n", 
            test_info.total, 
            test_info.success 
            );
    }
    return 0;
}

void add_function(TestFuncT func, const char *str) {
    struct Function *temp = (struct Function *)calloc(1, sizeof(struct Function)); 
    temp->func = func;
    temp->str = strdup(str);
    func_tail->pointer.next = &(temp->pointer);
    func_tail = temp;
    return ;
}
