#include <vector>
#include <algorithm>
#include <iostream>
#include <gtest/gtest.h>

int Partition(std::vector<int> &nums, int start, int end) {
    int pivot = nums[end];
    int idx = start;
    for (int i = start; i < end; i++)
        if (nums[i] < pivot)
            std::swap(nums[idx++], nums[i]);

    std::swap(nums[idx], nums[end]);
    return idx;
}

void QuickSort(std::vector<int> &nums, int start, int end) {
    if (start >= end) return;
    int mid = Partition(nums, start, end);
    QuickSort(nums, start, mid-1);
    QuickSort(nums, mid+1, end);
}

TEST(TestQuickSortSuite, TestQuickSort) {
    std::vector<int> nums{0,7,8,9,6,3,2,1,4,5};
    QuickSort(nums, 0, nums.size()-1);
    std::vector<int> want{0,1,2,3,4,5,6,7,8,9};
    ASSERT_EQ(want, nums);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}