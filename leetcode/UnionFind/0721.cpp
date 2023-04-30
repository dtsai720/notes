#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

class DSU {
private:
    vector<int> parent;
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
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        const int m = accounts.size();
        unordered_map<string, int> mymap;
        DSU u(m);
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (mymap.count(email) == 0)
                    mymap[email] = i;
                else
                    u.Union(mymap[email], i);
            }
        }

        vector<vector<string>> merge(m);
        for (auto p: mymap) {
            string email = p.first;
            int x = p.second;
            merge[u.find(x)].push_back(email);
        }

        vector<vector<string>> output;
        for (int i = 0; i < m; i++) {
            if (merge[i].empty()) continue;
            string name = accounts[i][0];
            vector<string> account{name};
            sort(merge[i].begin(), merge[i].end());
            account.insert(account.end(), merge[i].begin(), merge[i].end());
            output.push_back(account);
        }
        return output;
    }
};

TEST(TestAccountsMergeSuite, TestAccountsMerge1) {
    Solution solution = Solution();
    vector<vector<string>> in{{"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},{"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}};
    vector<vector<string>> want{{"John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"},
        {"Mary","mary@mail.com"},{"John","johnnybravo@mail.com"}};
    ASSERT_EQ(want, solution.accountsMerge(in));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}