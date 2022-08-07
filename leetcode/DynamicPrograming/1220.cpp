#include <gtest/gtest.h>

#define MOD 1000000007

class Solution {
public:
    int countVowelPermutation(int n);
};

int Solution::countVowelPermutation(int n) {
    long long int dp[n+1][5];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < 5; i++) dp[1][i] = 1;
    for (int i = 2; i < n+1; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][1] = (dp[i-1][0]+dp[i-1][2])%MOD;
        dp[i][2] = (dp[i-1][0]+dp[i-1][1]+dp[i-1][3]+dp[i-1][4])%MOD;
        dp[i][3] = (dp[i-1][2]+dp[i-1][4])%MOD;
        dp[i][4] = dp[i-1][0]; 
    }
    long long int result = 0;
    for (int i = 0; i < 5; i++) result += dp[n][i];
    return result%MOD;
}

TEST(TestCountVowelPermutationSuite, TestCountVowelPermutation) {
    Solution solution = Solution();
    ASSERT_EQ(5, solution.countVowelPermutation(1));
    ASSERT_EQ(10, solution.countVowelPermutation(2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}