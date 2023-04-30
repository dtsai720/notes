#include <vector>
#include <numeric>
#include <gtest/gtest.h>

using namespace std;

class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int m): parent(m), rank(m) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x? x: parent[x] = find(parent[x]);
    }

    bool Union(int x, int y) {
        // optimized
        int a = find(x), b = find(y);
        if (a == b) return false;
        if (rank[a] > rank[b]) parent[b] = a;
        else if (rank[a] < rank[b]) parent[a] = b;
        else {
            parent[a] = b;
            rank[b]++;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int x = -1, y = -1;
        const int m = edges.size();
        DSU u(m+1);
        for (int i = 0; i < m; i++) {
            int from = edges[i][0], to = edges[i][1];
            if (u.Union(from, to)) continue;
            x = from, y = to;
            break;
        }
        return {x, y};
    }
};

TEST(TestFindRedundantConnectionSuite, TestFindRedundantConnection1) {
    Solution solution = Solution();
    vector<vector<int>> in{{1,2},{1,3},{2,3}};
    vector<int> want{2,3};
    ASSERT_EQ(want, solution.findRedundantConnection(in));
}

TEST(TestFindRedundantConnectionSuite, TestFindRedundantConnection2) {
    Solution solution = Solution();
    vector<vector<int>> in{{1,2},{2,3},{3,4},{1,4},{1,5}};
    vector<int> want{1,4};
    ASSERT_EQ(want, solution.findRedundantConnection(in));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}