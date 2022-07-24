#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target);
};

bool Solution::searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    const int m = matrix.size(), n = matrix[0].size();
    int x = 0, y = n-1;
    while (x != m && y != -1) {
        if (matrix[x][y] == target) return true;
        matrix[x][y] > target? y--: x++;
    }
    return false;
}

TEST(TestSearchMatrixSuite, TestSearchMatrix) {
    Solution solution = Solution();
    std::vector<std::vector<int>> input{
        {1,4,7,11,15},
        {2,5,8,12,19},
        {3,6,9,16,22},
        {10,13,14,17,24},
        {18,21,23,26,30},
    };
    ASSERT_TRUE(solution.searchMatrix(input, 5));
    ASSERT_FALSE(solution.searchMatrix(input, 20));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}