#include <vector>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& nums);
};

void Solution::rotate(vector<vector<int>>& nums) {
    const int m = nums.size();
    for (int i = 0; i < m/2+m%2; i++) {
        for (int j = 0; j < m/2; j++) {
            swap(nums[i][j], nums[j][m-1-i]);
            swap(nums[i][j], nums[m-1-i][m-1-j]);
            swap(nums[i][j], nums[m-1-j][i]);
        }
    }
}

TEST(TestRotateSuite, example1) {
    Solution solution = Solution();
    vector<vector<int>> before{{1,2,3},{4,5,6},{7,8,9}};
    solution.rotate(before);
    vector<vector<int>> want{{7,4,1},{8,5,2},{9,6,3}};
    ASSERT_EQ(before, want);
}

TEST(TestRotateSuite, example2) {
    Solution solution = Solution();
    vector<vector<int>> before{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    solution.rotate(before);
    vector<vector<int>> want{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};
    ASSERT_EQ(before, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}