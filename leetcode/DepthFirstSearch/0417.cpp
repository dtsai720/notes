#include <vector>
#include <gtest/gtest.h>

using namespace std;

const vector<pair<int, int>> cursor{{1,0},{-1,0},{0,1},{0,-1}};

class Solution {
private:
    void dfs(vector<vector<bool>>& visited, vector<vector<int>>& nums, int x, int y);
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> nums);
};

void Solution::dfs(vector<vector<bool>>& visited, vector<vector<int>>& nums, int x, int y) {
    if (visited[x][y]) return;
    const int m = nums.size(), n = nums[0].size();
    visited[x][y] = true;
    for (auto& cur: cursor) {
        const int row = x+cur.first, col = y+cur.second;
        if (-1 == row || -1 == col || m == row || n == col || nums[x][y] > nums[row][col]) continue;
        this->dfs(visited, nums, row, col);
    }
}

vector<vector<int>> Solution::pacificAtlantic(vector<vector<int>> nums) {
    const int m = nums.size(), n = nums[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n)), atlantic(m, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        this->dfs(pacific, nums, i, 0);
        this->dfs(atlantic, nums, i, n-1);
    }

    for (int i = 0; i < n; i++) {
        this->dfs(pacific, nums, 0, i);
        this->dfs(atlantic, nums, m-1, i);
    }
    vector<vector<int>> result;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (pacific[i][j] && atlantic[i][j])
                result.push_back({i,j});
    return result;
}

TEST(TestPacificAtlanticSuite, example1) {
    Solution solution = Solution();
    vector<vector<int>> actual = solution.pacificAtlantic({{1}});
    vector<vector<int>> want = {{0,0}};
    ASSERT_EQ(want, actual);
}

TEST(TestPacificAtlanticSuite, example2) {
    Solution solution = Solution();
    vector<vector<int>> actual = solution.pacificAtlantic({
        {1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}});
    vector<vector<int>> want = {{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0}};
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}