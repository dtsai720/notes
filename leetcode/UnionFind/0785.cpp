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
    bool isBipartite(std::vector<std::vector<int>>& graph) {
        const int m = graph.size();
        DSU u(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (u.find(i) == u.find(graph[i][j])) return false;
                u.Union(graph[i][0], graph[i][j]);
            }
        }
        return true;
    }
};

TEST(TestIsBipartiteSuite, TestIsBipartite1) {
    Solution solution = Solution();
    std::vector<std::vector<int>> in{{1,2,3},{0,2},{0,1,3},{0,2}};
    ASSERT_FALSE(solution.isBipartite(in));
}

TEST(TestIsBipartiteSuite, TestIsBipartite2) {
    Solution solution = Solution();
    std::vector<std::vector<int>> in{{1,3},{0,2},{1,3},{0,2}};
    ASSERT_TRUE(solution.isBipartite(in));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}