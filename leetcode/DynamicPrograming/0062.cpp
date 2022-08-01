#include <gtest/gtest.h>

class Solution {
public:
    int uniquePaths(int m, int n);
};

int Solution::uniquePaths(int m, int n) {
    int dp[m][n];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = i == 0 || j == 0? 1: dp[i-1][j]+dp[i][j-1];
    return dp[m-1][n-1];
}

TEST(TestUniquePathsSuite, TestUniquePaths) {
    Solution solution = Solution();
    ASSERT_EQ(solution.uniquePaths(3, 7), 28);
    ASSERT_EQ(solution.uniquePaths(3, 2), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}