#include <vector>
#include <string>
#include <gtest/gtest.h>

class Solution {
private:
    int wordset[26];
    bool isSubset(std::string &word);
public:
    std::vector<std::string> wordSubsets(std::vector<std::string>& words1, std::vector<std::string>& words2);
};

bool Solution::isSubset(std::string &word) {
    int temp[26] = {0};
    for (char &c: word)
        temp[c-'a']++;
    for (int i = 0; i < 26; i++)
        if (this->wordset[i] > temp[i]) return false;
    return true;
}

std::vector<std::string> Solution::wordSubsets(std::vector<std::string>& words1, std::vector<std::string>& words2) {
    memset(this->wordset, 0, sizeof(this->wordset));
    for (std::string &word: words2) {
        int temp[26] = {0};
        for (char &c: word)
            temp[c-'a']++;
        for (int i = 0; i < 26; i++)
            this->wordset[i] = std::max(this->wordset[i], temp[i]);
    }
    
    std::vector<std::string> result;
    for (std::string word: words1)
        if (this->isSubset(word))
            result.push_back(word);
    return result;
}

TEST(TestWordSubsetsSuite, TestWordSubsets1) {
    Solution solution = Solution();
    std::vector<std::string> want{"facebook","google","leetcode"};
    std::vector<std::string> word1{"amazon","apple","facebook","google","leetcode"};
    std::vector<std::string> word2{"e","o"};
    std::vector<std::string> actual = solution.wordSubsets(word1, word2);
    ASSERT_EQ(actual, want);
}

TEST(TestWordSubsetsSuite, TestWordSubsets2) {
    Solution solution = Solution();
    std::vector<std::string> want{"apple","google","leetcode"};
    std::vector<std::string> word1{"amazon","apple","facebook","google","leetcode"};
    std::vector<std::string> word2{"l","e"};
    std::vector<std::string> actual = solution.wordSubsets(word1, word2);
    ASSERT_EQ(actual, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}