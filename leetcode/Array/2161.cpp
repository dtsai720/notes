#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    std::vector<int> pivotArray(std::vector<int> nums, int pivot);
};

std::vector<int> Solution::pivotArray(std::vector<int> nums, int pivot) {
    std::vector<int> prev, mid, post;
    for (int num: nums) {
        if (num > pivot) post.push_back(num);
        else if (num == pivot) mid.push_back(num);
        else prev.push_back(num);
    }
    prev.insert(prev.end(), mid.begin(), mid.end());
    prev.insert(prev.end(), post.begin(), post.end());
    return prev;
}

TEST(TestPivotArraySuite, TestPivotArray1) {
    Solution solution = Solution();
    std::vector<int> actual = solution.pivotArray({9,12,5,10,14,3,10}, 10);
    std::vector<int> want{9,5,3,10,10,12,14};
    ASSERT_EQ(want, actual);
}

TEST(TestPivotArraySuite, TestPivotArray2) {
    Solution solution = Solution();
    std::vector<int> actual = solution.pivotArray({-3,4,3,2}, 2);
    std::vector<int> want{-3,2,4,3};
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}