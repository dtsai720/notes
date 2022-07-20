#include <string>
#include <unordered_map>
#include <gtest/gtest.h>

class Solution {
private:
    bool isSubseq(std::string &s1, const std::string &s2);
public:
    int numMatchingSubseq(std::string s, std::vector<std::string> words);
};

bool Solution::isSubseq(std::string &s1, const std::string &s2) {
    size_t cur = 0;
    for (size_t i = 0; i < s1.length() && cur < s2.length(); i++)
        if (s1[i] == s2[cur]) cur++;
    return cur == s2.length();
}

int Solution::numMatchingSubseq(std::string s, std::vector<std::string> words) {
    int result = 0;
    std::unordered_map<std::string, int> mymap;
    for (std::string word: words) mymap[word]++;
    for (const std::pair<std::string, int> p: mymap)
        result += this->isSubseq(s, p.first)? p.second: 0;
    return result;
}

TEST(TestNumMatchingSubseqSuite1, TestNumMatchingSubseq) {
    Solution solution = Solution();
    ASSERT_EQ(solution.numMatchingSubseq("abcde", {"a","bb","acd","ace"}), 3);
}

TEST(TestNumMatchingSubseqSuite3, TestNumMatchingSubseq) {
    Solution solution = Solution();
    ASSERT_EQ(solution.numMatchingSubseq("dsahjpjauf", {"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"}), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}