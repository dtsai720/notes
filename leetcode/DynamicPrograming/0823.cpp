#include <bits/stdc++.h>
#include <gtest/gtest.h>

#define MOD 1000000007

class Solution {
public:
    int numFactoredBinaryTrees(std::vector<int> arr);
};

TEST(TestNumFactoredBinaryTreesSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(3, solution.numFactoredBinaryTrees({15,13,22,7,11}));
    ASSERT_EQ(7, solution.numFactoredBinaryTrees({2,4,5,10}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}