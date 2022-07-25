#include <vector>
#include <gtest/gtest.h>

void Merge(std::vector<int>& nums, int start, int end, int mid) {
    std::vector<int> left(nums.begin()+start, nums.begin()+mid+1);
    std::vector<int> right(nums.begin()+mid+1, nums.begin()+end+1);

    left.push_back(INT32_MAX);
    right.push_back(INT32_MAX);

    int idxLeft = 0, idxRight = 0;
    for (int i = start; i <= end; i++)
        nums[i] = left[idxLeft] >= right[idxRight]? right[idxRight++]:left[idxLeft++];
}

void MergeSort(std::vector<int>& nums, int start, int end) {
    if (start >= end) return;
    int mid = (start+end)/2;
    MergeSort(nums, start, mid);
    MergeSort(nums, mid+1, end);
    Merge(nums, start, end, mid);
}

TEST(TestMergeSortSuite, TestMergeSort) {
    std::vector<int> nums{1,3,2,4,5,100};
    MergeSort(nums, 0, nums.size()-1);
    std::vector<int> want{1,2,3,4,5,100};
    ASSERT_EQ(nums, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}