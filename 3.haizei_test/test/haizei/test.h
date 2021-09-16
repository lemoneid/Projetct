/*************************************************************************
	> File Name: test.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年06月20日 星期六 14时07分27秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#include <haizei/linklist.h>
#define Name(a, b) a##_test_##b
#define Str(a, b)  #a "_test_" #b

#define TEST(a, b)\
void a##_test_##b();\
__attribute__((constructor))\
void add_##a##__test__##b() {\
    add_function(Name(a,b), Str(a, b));\
}\
void a##_test_##b()\


#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define COLOR_HL(a, b) "\033[" #b ";1m" a "\033[0m"

#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define BLUE(a) COLOR(a, 34)
#define YELLOW(a) COLOR(a, 33)

#define GREEN_HL(a) COLOR_HL(a, 32)
#define RED_HL(a) COLOR_HL(a, 31)
#define BLUE_HL(a) COLOR_HL(a, 34)
#define YELLOW_HL(a) COLOR_HL(a, 33)
#define TYPE_STR(a) _Generic((a), \
    int : "%d", \
    double : "%lf", \
    float : "%f", \
    long long : "%lld",\
    char : "%c", \
    const char * : "%s",\
    default : "others"\
)

#define P(a, color) {\
    char frm[1000];\
    sprintf(frm, color("%s"), TYPE_STR(a));\
    printf(frm, a);\
}

#define EXPECT(a, b, comp) {\
        __typeof(a) _a = (a);\
        __typeof(b) _b = (b);\
        test_info.total += 1;\
        if (_a comp _b) test_info.success += 1;\
        else {\
            printf(YELLOW_HL("\n\t%s:%d: Failure\n"), __FILE__, __LINE__);\
            printf(YELLOW_HL("\t\texpect : " #a " " #comp " " #b "\n\t\t" "actual : "));\
            P(_a, YELLOW_HL);\
            printf(YELLOW_HL(" vs "));\
            P(_b, YELLOW_HL);\
            printf("\n\n");\
        }\
        printf(GREEN("[-----------] ") #a " " #comp " " #b);\
        printf(" %s\n", (_a comp _b ? GREEN_HL("True") : RED_HL("False")));\
}

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)

typedef void (*TestFuncT)();
struct Function {
    TestFuncT func;
    const char *str;
    struct LinkNode pointer;
};

struct FunctionInfo {
    int total, success;
};

extern struct FunctionInfo test_info;

int RUN_ALL_TESTS();
void add_function(TestFuncT, const char *);


#endif
