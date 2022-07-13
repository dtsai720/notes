#include <vector>
#include <numeric>
#include <gtest/gtest.h>

class Solution {
private:
    bool backtrace(std::vector<int>& nums, std::vector<int>& arr, int idx) {
        if (idx == nums.size())
            return std::accumulate(arr.begin(), arr.end(), 0) == 0;
        for (int side = 0; side < 4; side++) {
            if (arr[side] < nums[idx]) continue;
            arr[side] -= nums[idx];
            if (backtrace(nums, arr, idx+1)) return true;
            arr[side] += nums[idx];
        }
        return false;
    }
public:
    bool makesquare(std::vector<int>& matchsticks) {
        int total = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (total % 4 != 0) return false;
        std::sort(matchsticks.rbegin(), matchsticks.rend());
        std::vector<int> arr(4, total/4);
        return backtrace(matchsticks, arr, 0);
    }
};

TEST(TestMakeSquareSuite, TestMakeSquarePass) {
    std::vector<int> in{1,1,2,2,2};
    Solution solution = Solution();
    ASSERT_TRUE(solution.makesquare(in));
}

TEST(TestMakeSquareSuite, TestMakeSquareFail) {
    std::vector<int> in{3,3,3,3,4};
    Solution solution = Solution();
    ASSERT_FALSE(solution.makesquare(in));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}