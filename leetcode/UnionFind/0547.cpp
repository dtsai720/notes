#include <vector>
#include <gtest/gtest.h>

using namespace std;

class Solution {
private:
    void _union(vector<int>& array, int x, int y) {
        int a = find(array, x), b = find(array, y);
        if (a != b) array[a] = b;
    }

    int find(vector<int>& array, int x) {
        return array[x] == -1? x: array[x] = find(array, array[x]);
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        const int m = isConnected.size();
        vector<int> array(m, -1);
        for (int from = 0; from < m; from++) {
            for (int to = 0; to < m; to++) {
                if (isConnected[from][to] == 0) continue;
                _union(array, from, to);
            }
        }
        int count = 0;
        for (int i = 0; i < m; i++) count += array[i] == -1;
        return count;
    }
};

TEST(TestFindCircleNumSuite, TestFindCircleNum1) {
    Solution solution = Solution();
    vector<vector<int>> in{{1,1,0},{1,1,0},{0,0,1}};
    ASSERT_EQ(2, solution.findCircleNum(in));
}

TEST(TestFindCircleNumSuite, TestFindCircleNum2) {
    Solution solution = Solution();
    vector<vector<int>> in{{1,0,0},{0,1,0},{0,0,1}};
    ASSERT_EQ(3, solution.findCircleNum(in));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}