#include <vector>
#include <string>
#include <gtest/gtest.h>

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string> words);
};

bool Solution::wordBreak(std::string s, std::vector<std::string> words) {
    const int m = s.length();
    bool dp[m+1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (int i = 1; i <= m; i++) {
        for (std::string &want: words) {
            const int size = want.length();
            if (i - size < 0) continue;
            dp[i] |= dp[i-size] && s.substr(i-size, size) == want;
        }
    }
    return dp[m];
}

TEST(TestWorkBreakISuite, TestWorkBreak) {
    Solution solution = Solution();
    ASSERT_TRUE(solution.wordBreak("leetcode", {"leet","code"}));
    ASSERT_TRUE(solution.wordBreak("applepenapple", {"apple","pen"}));
    ASSERT_FALSE(solution.wordBreak("catsandog", {"cats","dog","sand","and","cat"}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}