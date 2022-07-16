#include <vector>
#include <gtest/gtest.h>

#define MOD 1000000007;

class Solution {
private:
    const std::vector<std::pair<int, int>> cursor{{1,0},{-1,0},{0,1},{0,-1}};
    int memo[51][51][51];
    int helper(int m, int n, int k, int x, int y);
public:
    int findPaths(int m, int n, int k, int x, int y);
};

int Solution::helper(int m, int n, int k, int x, int y) {
    if (-1 == x || -1 == y || m == x || n == y) return 1;
    if (0 == k) return 0;
    if (this->memo[x][y][k] != -1) return this->memo[x][y][k];
    long long int result = 0;
    for (const std::pair<int, int> &cur: cursor)
        result += this->helper(m, n, k-1, x+cur.first, y+cur.second);
    return this->memo[x][y][k] = result%MOD;
}

int Solution::findPaths(int m, int n, int k, int x, int y) {
    memset(this->memo, -1, sizeof(this->memo));
    return this->helper(m, n, k, x, y);
}

TEST(TestFindPathsSuite, TestFindPaths) {
    Solution solution = Solution();
    EXPECT_EQ(solution.findPaths(2,2,2,0,0), 6);
    EXPECT_EQ(solution.findPaths(1,3,3,0,1), 12);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}