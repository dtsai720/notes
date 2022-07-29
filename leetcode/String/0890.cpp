#include <string>
#include <vector>
#include <gtest/gtest.h>

class Solution {
private:
    bool isMatch(std::string &word, std::string &pattern);
public:
    std::vector<std::string> findAndReplacePattern(std::vector<std::string>& words, std::string pattern);
};

bool Solution::isMatch(std::string &word, std::string &pattern) {
    const int m = pattern.length();
    if (word.length() != m) return false;
    int wordToPattern[27] = {0}, patternToWord[27] = {0};

    for (int i = 0; i < m; i++) {
        const int w = word[i] - 'a'+1, p = pattern[i] - 'a'+1;
        if (wordToPattern[w] != 0 && wordToPattern[w] != p) return false;
        if (patternToWord[p] != 0 && patternToWord[p] != w) return false;
        wordToPattern[w] = p, patternToWord[p] = w;
    }
    return true;
}

std::vector<std::string> Solution::findAndReplacePattern(std::vector<std::string>& words, std::string pattern) {
    std::vector<std::string> result;
    for (std::string &word: words)
        if (this->isMatch(word, pattern))
            result.push_back(word);
    return result;
}

TEST(TestFindAndReplacePatternSuite, TestFindAndReplacePattern1) {
    Solution solution = Solution();
    std::vector<std::string> input{"abc","deq","mee","aqq","dkd","ccc"};
    std::vector<std::string> want{"mee","aqq"};
    std::vector<std::string> actual = solution.findAndReplacePattern(input, "abb");
    ASSERT_EQ(want, actual);
}

TEST(TestFindAndReplacePatternSuite, TestFindAndReplacePattern2) {
    Solution solution = Solution();
    std::vector<std::string> input{"a","b","c"};
    std::vector<std::string> want{"a","b","c"};
    std::vector<std::string> actual = solution.findAndReplacePattern(input, "a");
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}