#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

void BubbleSort(std::vector<int>& nums) {
    const int m = nums.size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m-i; j++)
            if (nums[j+1] < nums[j])
                std::swap(nums[j], nums[j+1]);
}

TEST(TestBubbleSortSuite, TestBubbleSort) {
    std::vector<int> nums{3,4,1,5,7,9,1,0};
    std::vector<int> want{0,1,1,3,4,5,7,9};
    BubbleSort(nums);
    ASSERT_EQ(nums, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}