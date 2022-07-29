#include <vector>
#include <gtest/gtest.h>

class Solution {
private:
    int dp[1001][101][2];
    int dfs(std::vector<int> &prices, int idx, int k, int buy);
public:
    int maxProfit(int k, std::vector<int> prices);
};

int Solution::dfs(std::vector<int> &prices, int idx, int k, int buy) {
    if (idx == prices.size() || k == 0) return 0;
    if (dp[idx][k][buy] != -1) return dp[idx][k][buy];
    return dp[idx][k][buy] = buy == 1?
        std::max(this->dfs(prices, idx+1, k, 1), this->dfs(prices, idx+1, k, 0)-prices[idx]):
        std::max(this->dfs(prices, idx+1, k, 0), this->dfs(prices, idx+1, k-1, 1)+prices[idx]);
}

int Solution::maxProfit(int k, std::vector<int> prices) {
    memset(this->dp, -1, sizeof(this->dp));
    return this->dfs(prices, 0, k, 1);
}

TEST(TestMaxProfitSuite, TestMaxProfit) {
    Solution solution = Solution();
    ASSERT_EQ(solution.maxProfit(2, {2,4,1}), 2);
    ASSERT_EQ(solution.maxProfit(2, {3,2,6,5,0,3}), 7);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}