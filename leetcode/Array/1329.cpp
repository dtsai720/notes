#include <vector>
#include <queue>
#include <unordered_map>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>> nums);
};

vector<vector<int>> Solution::diagonalSort(vector<vector<int>> nums) {
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> mymap;
    const int m = nums.size(), n = nums[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            mymap[i-j].push(nums[i][j]);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            nums[i][j] = mymap[i-j].top();
            mymap[i-j].pop();
        }
    }
    return nums;
}

TEST(TestDiagonalSortSuite, example) {
    Solution solution = Solution();
    vector<vector<int>> result = solution.diagonalSort({{3,3,1,1},{2,2,1,2},{1,1,1,2}});
    vector<vector<int>> want = {{1,1,1,1},{1,2,2,2},{1,2,3,3}};
    ASSERT_EQ(want, result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}