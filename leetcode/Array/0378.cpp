#include <vector>
#include <queue>
#include <gtest/gtest.h>

class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>> matrix, int k);
};

int Solution::kthSmallest(std::vector<std::vector<int>> matrix, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (std::vector<int> &nums: matrix)
        for (int num: nums)
            pq.push(num);
    while (--k > 0)
        pq.pop();
    return pq.top();
}

TEST(TestKthSamllestSuite, TestKthSamllest) {
    Solution solution = Solution();
    ASSERT_EQ(13, solution.kthSmallest({{1,5,9},{10,11,13},{12,13,15}}, 8));
    ASSERT_EQ(-5, solution.kthSmallest({{-5}}, 1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}