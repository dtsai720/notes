#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& nums) {
        unordered_map<int, int> mymap;
        vector<int> result, numbers;
        for (const int num: nums) {
            if (++mymap[num] == 1)
                numbers.emplace_back(num);
        }
        sort(numbers.begin(), numbers.end());
        for (const int num: numbers) {
            int count = mymap[num];
            if (count == 0) continue;
            if (num == 0 && count % 2 == 1) return {};
            if (mymap[num*2] < count) return {};
            count = num == 0? count/2: count;
            for (int i = 0; i < count; i++) result.emplace_back(num);
            mymap[num] = 0;
            mymap[2*num] -= count;
        }
        return result;
    }
};

TEST(TestFindOriginalArray, example) {
    Solution solution = Solution();
    vector<int> in{0,0,0,0,1,1,2,2,2,4};
    vector<int> want{0,0,1,1,2};
    vector<int> actual = solution.findOriginalArray(in);
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}