#include <vector>
#include <gtest/gtest.h>

class Solution {
private:
    int findMinIndex(std::vector<int>& nums, int target);
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target);
};

int Solution::findMinIndex(std::vector<int>& nums, int target) {
    int start = 0, end = nums.size(), mid = 0;
    while (start < end) {
        mid = (start+end)/2;
        nums[mid] >= target? end = mid: start=mid+1;
    }
    return start;
}

std::vector<int> Solution::searchRange(std::vector<int>& nums, int target) {
    const int left = this->findMinIndex(nums, target);
    if (left == nums.size() || nums[left] != target) return {-1,-1};
    const int right = this->findMinIndex(nums, target+1)-1;
    return {left,right};
}

TEST(TestSearchRangeSuite, TestSearchRange1) {
    Solution solution = Solution();
    std::vector<int> input{5,7,7,8,8,10};
    std::vector<int> want{3,4};
    std::vector<int> actual = solution.searchRange(input, 8);
    ASSERT_EQ(want, actual);
}

TEST(TestSearchRangeSuite, TestSearchRange2) {
    Solution solution = Solution();
    std::vector<int> input{5,7,7,8,8,10};
    std::vector<int> want{-1,-1};
    std::vector<int> actual = solution.searchRange(input, 6);
    ASSERT_EQ(want, actual);
}

TEST(TestSearchRangeSuite, TestSearchRange3) {
    Solution solution = Solution();
    std::vector<int> input;
    std::vector<int> want{-1,-1};
    std::vector<int> actual = solution.searchRange(input, 0);
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}