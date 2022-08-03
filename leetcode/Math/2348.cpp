#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    long long zeroFilledSubarray(std::vector<int> nums);
};

long long Solution::zeroFilledSubarray(std::vector<int> nums) {
    nums.push_back(-1);
    long long int count = 0;
    long long int result = 0;
    for (int num: nums) {
        if (num == 0) {
            count++;
            continue;
        }
        result += (count * (count+1)/2);
        count = 0;
    }
    return result;
}

TEST(TestZeroFilledSubarraySuite, TestZeroFilledSubarray) {
    Solution solution = Solution();
    ASSERT_EQ(solution.zeroFilledSubarray({1,3,0,0,2,0,0,4}), 6);
    ASSERT_EQ(solution.zeroFilledSubarray({0,0,0,2,0,0}), 9);
    ASSERT_EQ(solution.zeroFilledSubarray({2,10,2019}), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}