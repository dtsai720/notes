#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int combinationSum4(std::vector<int> nums, int target);
};

int Solution::combinationSum4(std::vector<int> nums, int target) {
    std::vector<unsigned long long int> dp(target+1, 0);
    std::sort(nums.begin(), nums.end());
    dp[0] = 1;

    for (int i = 1; i < target+1; i++) {
        for (int num: nums) {
            if (num > i) break;
            dp[i] += dp[i-num];
        }
    }

    return dp[target];
}

TEST(TestCombinationSum4Suite, TestCombinationSum4) {
    Solution solution = Solution();
    ASSERT_EQ(solution.combinationSum4({1,2,3},4), 7);
    ASSERT_EQ(solution.combinationSum4({9},3), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}