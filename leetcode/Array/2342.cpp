#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

class Solution {
private:
    int SumOfDigits(int n);
public:
    int maximumSum(std::vector<int> nums);
};

int Solution::SumOfDigits(int n) {
    return n > 9? n % 10 + this->SumOfDigits(n / 10): n;
}

int Solution::maximumSum(std::vector<int> nums) {
    sort(nums.begin(), nums.end());
    std::unordered_map<int, std::vector<int>> mymap;
    for (int num: nums) mymap[this->SumOfDigits(num)].push_back(num);

    int result = -1;
    for (const std::pair<int, std::vector<int>> &row: mymap) {
        if (row.second.size() < 2) continue;
        const int size = row.second.size();
        const int m = row.second.back()+row.second[size-2];
        result = std::max(result, m);
    }
    return result;
}

TEST(TestMaximumSumSuite, TestMaximumSum) {
    Solution solution = Solution();
    ASSERT_EQ(solution.maximumSum({18,43,36,13,7}), 54);
    ASSERT_EQ(solution.maximumSum({10,12,19,14}), -1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}