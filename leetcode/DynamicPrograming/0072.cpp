#include <string>
#include <gtest/gtest.h>

class Solution {
public:
    int minDistance(std::string word1, std::string word2);
};

int minValue(int a, int b, int c) {
    if (a < b && a < c) return a;
    return b > c? c: b;
}

int Solution::minDistance(std::string s1, std::string s2) {
    const int m = s1.length();
    const int n = s2.length();
    int dp[m+1][n+1];
    memset(dp, INT32_MAX, sizeof(dp));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int i = 0; i <= n; i++) dp[0][i] = i;
    s1 = ' '+s1, s2 = ' '+s2;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = s1[i] == s2[j]? dp[i-1][j-1]: 1+minValue(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);

    return dp[m][n];
}

TEST(TestMinDistanceSuite, TestMinDistance) {
    Solution solution = Solution();
    ASSERT_EQ(solution.minDistance("horse", "ros"), 3);
    ASSERT_EQ(solution.minDistance("intention", "execution"), 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}