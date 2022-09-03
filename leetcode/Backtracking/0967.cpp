#include <vector>
#include <gtest/gtest.h>

using namespace std;

class Solution {
private:
    void backtrace(vector<int>& output, int n, int k, int num);
public:
    vector<int> numsSameConsecDiff(int n, int k);
};

void Solution::backtrace(vector<int>& output, int n, int k, int num) {
    if (0 == n) {
        output.push_back(num);
        return;
    }
    for (int i = num==0; i < 10; i++) {
        if (num != 0 && abs(num%10-i) != k) continue;
        this->backtrace(output, n-1, k, 10*num+i);
    }
}

vector<int> Solution::numsSameConsecDiff(int n, int k) {
    vector<int> output;
    this->backtrace(output, n, k, 0);
    return output;
}

TEST(TestNumsSameConsecDiffSuite, example1) {
    Solution solution = Solution();
    vector<int> want{181,292,707,818,929};
    ASSERT_EQ(want, solution.numsSameConsecDiff(3,7));
}

TEST(TestNumsSameConsecDiffSuite, example2) {
    Solution solution = Solution();
    vector<int> want{10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98};
    ASSERT_EQ(want, solution.numsSameConsecDiff(2,1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}