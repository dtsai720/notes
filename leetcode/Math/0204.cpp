#include <numeric>
#include <gtest/gtest.h>

class Solution {
public:
    int countPrimes(int n);
};

int Solution::countPrimes(int n) {
    bool mem[5000001];
    memset(mem, true, sizeof(mem));
    mem[0] = mem[1] = false;
    for (int i = 2; i * i < n; i++) {
        if (!mem[i]) continue;
        for (int j = i * i; j < n; j += i) mem[j] = false;
    }
    return std::accumulate(mem, mem+n, 0);
}

TEST(TestCountPrimesSuite, TestCountPrimes) {
    Solution solution = Solution();
    ASSERT_EQ(solution.countPrimes(10), 4);
    ASSERT_EQ(solution.countPrimes(0), 0);
    ASSERT_EQ(solution.countPrimes(1), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}