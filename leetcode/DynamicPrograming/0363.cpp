#include <vector>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>> nums, int k);
};

int Solution::maxSumSubmatrix(vector<vector<int>> nums, int k) {
    const int m = nums.size(), n = nums[0].size();
    long long int dp[m][n];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = nums[0][0];
    for (int i = 1; i < m; i++)
        dp[i][0] = dp[i-1][0]+nums[i][0];

    for (int i = 1; i < n; i++)
        dp[0][i] = dp[0][i-1]+nums[0][i];

    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = nums[i][j]+dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];

    int result = INT32_MIN;
    for (int x1 = 0; x1 < m; x1++) {
        for (int x2 = x1; x2 < m; x2++) {
            for (int y1 = 0; y1 < n; y1++) {
                for (int y2 = y1; y2 < n; y2++) {
                    long long int value = dp[x2][y2];
                    if (x1 > 0 && y1 > 0) value += dp[x1-1][y1-1];
                    if (x1 > 0) value -= dp[x1-1][y2];
                    if (y1 > 0) value -= dp[x2][y1-1];
                    if (value <= k && result < value) result = value;
                }
            }
        }
    }

    return result;
}

TEST(TestMaxSumSubmatrixSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(2, solution.maxSumSubmatrix({{1,0,1},{0,-2,3}},2));
    ASSERT_EQ(3, solution.maxSumSubmatrix({{2,2,-1}},3));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}