#include <string>
#include <gtest/gtest.h>

class Solution {
public:
    bool isMatch(std::string s, std::string p);
};

bool Solution::isMatch(std::string s, std::string p) {
    const int m = s.length(), n = p.length();
    bool dp[m+1][n+1];
    memset(dp, false, sizeof(dp));
    p = ' '+p, s = ' '+s;
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) dp[0][i] = p[i] == '*' && dp[0][i-1];

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j] == '*')
                dp[i][j] = dp[i][j-1] || dp[i-1][j];
            else if (p[j] == '?' || s[i] == p[j])
                dp[i][j] = dp[i-1][j-1];
        }
    }
    return dp[m][n];
}

TEST(TestWildcardIsMatchSuite, TestIsMatchWildcard) {
    Solution solution = Solution();
    ASSERT_FALSE(solution.isMatch("aa", "a"));
    ASSERT_TRUE(solution.isMatch("aa", "*"));
    ASSERT_FALSE(solution.isMatch("cb", "?a"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}