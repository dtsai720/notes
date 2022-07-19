#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int maxSubArray(std::vector<int> nums);
};

int Solution::maxSubArray(std::vector<int> nums) {
    int result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        nums[i] += std::max(0, nums[i-1]);
        result = std::max(result, nums[i]);
    }
    return result;
}

TEST(TestMaxSubArraySuite, TestMaxSubArray) {
    Solution solution = Solution();
    ASSERT_EQ(solution.maxSubArray({-2,1,-3,4,-1,2,1,-5,4}), 6);
    ASSERT_EQ(solution.maxSubArray({-1}), -1);
    ASSERT_EQ(solution.maxSubArray({5,4,-1,7,8}), 23);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}