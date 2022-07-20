
#include <vector>
#include <gtest/gtest.h>

class Solution {
private:
    const std::vector<std::pair<int, int>> cursor{{1,0},{-1,0},{0,1},{0,-1}};
    int countArea(std::vector<std::vector<int>> &grid, int x, int y);
public:
    int maxAreaOfIsland(std::vector<std::vector<int>> &grid);
};

int Solution::countArea(std::vector<std::vector<int>> &grid, int x, int y) {
    const int m = grid.size();
    const int n = grid[0].size();
    if (-1 == x || -1 == y || m == x || n == y || 0 == grid[x][y]) return 0;
    grid[x][y] = 0;
    int result = 1;
    for (const std::pair<int, int> &cur: cursor)
        result += this->countArea(grid, x+cur.first, y+cur.second);
    return result;
}

int Solution::maxAreaOfIsland(std::vector<std::vector<int>> &grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    int result = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result = std::max(result, this->countArea(grid, i, j));
    return result;
}

TEST(TestMaxAreaOfIslandSuite, TestMaxAreaOfIsland) {
    Solution solution = Solution();
    std::vector<std::vector<int>> six{
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0},
    };
    ASSERT_EQ(solution.maxAreaOfIsland(six), 6);

    std::vector<std::vector<int>> zero{{0,0,0,0,0,0,0,0}};
    ASSERT_EQ(solution.maxAreaOfIsland(zero), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}