#include <gtest/gtest.h>

class Solution {
public:
    int countOperations(int num1, int num2);
};

int Solution::countOperations(int num1, int num2) {
    if (num1 == 0 || num2 == 0) return 0;
    if (num1 < num2) return this->countOperations(num2, num1);
    return num1/num2+this->countOperations(num2, num1%num2);
}

TEST(TestCountOperationsSuite, TestCountOperations) {
    Solution solution = Solution();
    ASSERT_EQ(solution.countOperations(2, 3), 3);
    ASSERT_EQ(solution.countOperations(10, 10), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}