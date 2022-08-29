#include <vector>
#include <gtest/gtest.h>

const std::vector<std::pair<int, int>> cursor{{1,0},{-1,0},{0,1},{0,-1}};

class Solution {
private:
    void dfs(std::vector<std::vector<char>>& array, int x, int y);
public:
    int numIslands(std::vector<std::vector<char>> array);
};

void Solution::dfs(std::vector<std::vector<char>>& array, int x, int y) {
    const int m = array.size();
    const int n = array[0].size();
    if (-1 == x || -1 == y || m == x || n == y || '0' == array[x][y]) return;
    array[x][y] = '0';
    for (auto &cur: cursor)
        this->dfs(array, x+cur.first, y+cur.second);
}

int Solution::numIslands(std::vector<std::vector<char>> array) {
    const int m = array.size();
    const int n = array[0].size();
    int result = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result += array[i][j] == '1';
            this->dfs(array, i, j);
        }
    }
    return result;
}

TEST(TestNumIsLandsSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(1, solution.numIslands({
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'},
    }));
    ASSERT_EQ(3, solution.numIslands({
        {'1','1','0','1','0'},
        {'1','1','0','1','0'},
        {'0','0','1','0','0'},
        {'0','0','0','0','0'},
    }));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}