#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int minSteps(int n);
};

int Solution::minSteps(int n) {
    std::vector<int> dp(n+1, INT32_MAX);
    dp[0] = 0, dp[1] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 2; i*j <= n; j++)
            dp[i*j] = std::min(dp[i*j], dp[i]+j);
    return dp.back();
}

TEST(TestMinStepsSuite, TestMinSteps) {
    Solution solution = Solution();
    ASSERT_EQ(solution.minSteps(3), 3);
    ASSERT_EQ(solution.minSteps(1), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}