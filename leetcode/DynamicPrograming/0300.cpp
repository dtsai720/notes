#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int lengthOfLIS(std::vector<int> nums);
};

int Solution::lengthOfLIS(std::vector<int> nums) {
    int result = 1;
    const int m = nums.size();
    std::vector<int> dp(m, 0);
    dp[0] = 1;
    for (int i = 1; i < m; i++) {
        int count = 0;
        for (int j = 0; j < i; j++)
            count = nums[j] >= nums[i]? count: std::max(dp[j], count);
        result = std::max(result, dp[i] = ++count);
    }
    return result;
}

TEST(TestLengthOfLISSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(4, solution.lengthOfLIS({10,9,2,5,3,7,101,18}));
    ASSERT_EQ(4, solution.lengthOfLIS({0,1,0,3,2,3}));
    ASSERT_EQ(1, solution.lengthOfLIS({7,7,7,7,7,7,7}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}