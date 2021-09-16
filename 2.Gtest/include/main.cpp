/*************************************************************************
	> File Name: main.cpp
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年06月13日 星期六 15时01分03秒
 ************************************************************************/

#include <cstdio>
#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(func, add) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_EQ(add(3, 6), 8);
    EXPECT_EQ(add(0, 3), 3);

}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
    return 0;
}

