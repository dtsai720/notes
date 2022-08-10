#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> prices);
};

TEST(TestMaxProfit, TestMaxProfit) {
    Solution solution = Solution();
    ASSERT_EQ(3, solution.maxProfit({1,2,3,0,2}));
    ASSERT_EQ(0, solution.maxProfit({1}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}