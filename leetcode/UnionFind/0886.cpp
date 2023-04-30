#include <vector>
#include <numeric>
#include <gtest/gtest.h>

class DSU {
private:
    std::vector<int> parent;
public:
    DSU(int m): parent(m) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x? x: parent[x] = find(parent[x]);
    }

    void Union(int x, int y) {
        int a = find(x), b = find(y);
        if (a != b) parent[a] = b;
    }
};

class Solution {
public:
    bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes) {
        DSU u(2*N+1);
        // Like (1...N), Dislike(N+1...2N+1)
        for (std::vector<int>& nums: dislikes) {
            int x = nums[0], y = nums[1];
            u.Union(x, N+y);
            u.Union(y, N+x);
        }
        for (int x = 0; x <= N; x++) {
            if (u.find(x) == u.find(x+N)) return false;
        }
        return true;
    }
};

TEST(TestPossibleBipartitionSuite, TestPossibleBipartition1) {
    Solution solution = Solution();
    std::vector<std::vector<int>> in{{1,2},{1,3},{2,4}};
    ASSERT_TRUE(solution.possibleBipartition(4, in));
}

TEST(TestPossibleBipartitionSuite, TestPossibleBipartition2) {
    Solution solution = Solution();
    std::vector<std::vector<int>> in{{1,2},{1,3},{2,3}};
    ASSERT_FALSE(solution.possibleBipartition(4, in));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}