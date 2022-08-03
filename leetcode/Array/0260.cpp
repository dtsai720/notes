#include <vector>
#include <unordered_set>
#include <gtest/gtest.h>

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int> nums);
};

std::vector<int> Solution::singleNumber(std::vector<int> nums) {
    std::unordered_set<int> myset;
    for (int num: nums) {
        if (myset.count(num) == 0)
            myset.insert(num);
        else
            myset.erase(num);
    }
    return std::vector<int>(myset.begin(), myset.end());
}

TEST(TestSingleNumberSuite, TestSingleNumber) {
    Solution solution = Solution();
    std::vector<int> actual= solution.singleNumber({1,2,1,3,2,5});
    std::vector<int> want = {5, 3};
    ASSERT_EQ(actual, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}