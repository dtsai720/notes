#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

class Solution {
public:
    bool isPossible(std::vector<int> nums);
};

bool Solution::isPossible(std::vector<int> nums) {
    std::unordered_map<int, int> counter, endAt;
    for (int num: nums) counter[num]++;
    for (int num: nums) {
        if (counter[num] == 0) continue;
        counter[num]--;
        if (endAt[num-1] > 0) {
            endAt[num-1]--;
            endAt[num]++;
        } else if (counter[num+1] > 0 && counter[num+2] > 0) {
            counter[num+1]--;
            counter[num+2]--;
            endAt[num+2]++;
        } else
            return false;
    }
    return true;
}

TEST(TestIsPossibleSuite, example) {
    Solution solution = Solution();
    ASSERT_TRUE(solution.isPossible({1,2,3,3,4,5}));
    ASSERT_TRUE(solution.isPossible({1,2,3,3,4,4,5,5}));
    ASSERT_FALSE(solution.isPossible({1,2,3,4,4,5}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}