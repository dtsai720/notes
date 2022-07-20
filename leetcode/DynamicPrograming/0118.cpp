#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    std::vector<std::vector<int>> generate(int numRows);
};

std::vector<std::vector<int>> Solution::generate(int numRows) {
    std::vector<std::vector<int>> result{{1}};
    for (int i = 1; i < numRows; i++) {
        std::vector<int> back = result.back();
        std::vector<int> cur{1};
        for (int j = 1; j < back.size(); j++)
            cur.push_back(back[j]+back[j-1]);
        cur.push_back(1);
        result.push_back(cur);
    }
    return result;
}

TEST(TestGenerateSuite, TestGenerate) {
    Solution solution = Solution();
    std::vector<std::vector<int>> want{{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}};
    std::vector<std::vector<int>> actual = solution.generate(5);
    ASSERT_EQ(actual, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}