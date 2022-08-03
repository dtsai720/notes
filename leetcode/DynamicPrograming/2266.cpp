#include <string>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#define MOD 1000000007

class Solution {
private:
    void setup(std::vector<long long int> &dp, int size);
public:
    int countTexts(std::string pressedKeys);
};

void Solution::setup(std::vector<long long int> &dp, int size) {
    for (int i = 1; i < size+1; i++) {
        for (int j = 0; j < i; j++)
            dp[i] += dp[i-j];
        dp[i] += 1;
    }

    for (int i = size+1; i < dp.size(); i++) {
        for (int j = 1; j < size+1; j++)
            dp[i] += dp[i-j];
        dp[i] %= MOD;
    }
}

int Solution::countTexts(std::string pressedKeys) {
    std::vector<std::pair<int, int>> array;
    pressedKeys.push_back(' ');
    char datum = pressedKeys[0];
    std::pair<int, int> length{3,4};
    int count = 0;
    for (char &c: pressedKeys) {
        if (datum == c) {
            count++;
            continue;
        }
        const int size = datum == '7' || datum == '9'? 4: 3;
        if (size == 3 )
            length.first = std::max(length.first, count);
        else
            length.second = std::max(length.second, count);

        array.push_back({size, count});
        datum = c, count = 1;
    }
    std::vector<long long int> dp3(length.first+1, 0);
    std::vector<long long int> dp4(length.second+1, 0);
    this->setup(dp3, 3);
    this->setup(dp4, 4);

    long long int result = 1;
    for (std::pair<int, int> &p: array) {
        result *= p.first == 3? dp3[p.second]: dp4[p.second];
        result %= MOD;
    }
    return result;
}

TEST(TestCountTextsSuite, TestCountTexts) {
    Solution solution = Solution();
    ASSERT_EQ(solution.countTexts("22233"), 8);
    ASSERT_EQ(solution.countTexts("222222222222222222222222222222222222"), 82876089);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}