#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int coinChange(std::vector<int> &coins, int amount);
};

int Solution::coinChange(std::vector<int> &coins, int amount) {
    std::vector<int> dp(amount+1, INT32_MAX);
    dp[0] = 0;
    for (int i = 1; i < amount+1; i++) {
        for (int coin: coins) {
            if (i < coin || dp[i-coin] == INT32_MAX) continue;
            dp[i] = std::min(dp[i], 1+dp[i-coin]);
        }
    }
    return dp[amount] == INT32_MAX? -1: dp[amount];
}

TEST(TestCoinChangeSuite, TestCoinChange1) {
    Solution solution = Solution();
    std::vector<int> nums{1,2,5};
    ASSERT_EQ(solution.coinChange(nums, 11), 3);
}

TEST(TestCoinChangeSuite, TestCoinChange2) {
    Solution solution = Solution();
    std::vector<int> nums{2};
    ASSERT_EQ(solution.coinChange(nums, 3), -1);
}

TEST(TestCoinChangeSuite, TestCoinChange3) {
    Solution solution = Solution();
    std::vector<int> nums{1};
    ASSERT_EQ(solution.coinChange(nums, 0), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}