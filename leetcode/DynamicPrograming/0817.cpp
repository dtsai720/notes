#include <vector>
#include <gtest/gtest.h>

class Solution {
public:
    int minRefuelStops(int target, int fuel, std::vector<std::vector<int>> stations);
};

int Solution::minRefuelStops(int target, int fuel, std::vector<std::vector<int>> stations) {
    std::vector<long long int> dp(stations.size()+1);
    dp[0] = fuel;
    for (int i = 0; i < stations.size(); i++) {
        std::vector<int> item = stations[i];
        for (int j = i; j > -1; j--) {
            if (dp[j] < item[0]) continue;
            if (dp[j] + item[1] > dp[j+1]) dp[j+1] = dp[j]+item[1];
        }
    }
    for (int i = 0; i < dp.size(); i++) {
        if(dp[i] >= target) return i;
    }
    return -1;
}

TEST(TestMinRefuelStopsSuite, example) {
    Solution solution = Solution();
    ASSERT_EQ(0, solution.minRefuelStops(1, 1, {}));
    ASSERT_EQ(-1, solution.minRefuelStops(100, 1, {{10, 100}}));
    ASSERT_EQ(2, solution.minRefuelStops(100, 10, {{10, 60},{20,30},{30,30},{60,40}}));
}

int main(int argc, char**argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}