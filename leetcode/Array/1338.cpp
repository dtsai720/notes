#include <vector>
#include <unordered_map>
#include <queue>
#include <gtest/gtest.h>

class Solution {
public:
    int minSetSize(std::vector<int> arr);
};

int Solution::minSetSize(std::vector<int> arr) {
    std::unordered_map<int, int> mymap;
    for (int num: arr) mymap[num]++;
    std::priority_queue<int> q;
    for (std::pair<int, int> item: mymap) q.push(item.second);
    int count = 0, result = 0;
    while (count*2 < arr.size()) {
        result++;
        count += q.top();
        q.pop();
    }
    return result;
}

TEST(TestMinSetSizeSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(2, solution.minSetSize({3,3,3,3,5,5,5,2,2,7}));
    ASSERT_EQ(1, solution.minSetSize({7,7,7,7,7,7}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}