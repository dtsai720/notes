#include <vector>
#include <string>
#include <gtest/gtest.h>

class Solution {
private:
    bool isSubset(std::string &word, int *array);
public:
    std::vector<std::string> wordSubsets(std::vector<std::string>& words1, std::vector<std::string>& words2);
};

bool Solution::isSubset(std::string &word, int *array) {
    int temp[26] = {0};
    for (char &c: word)
        temp[c-'a']++;
    for (int i = 0; i < 26; i++)
        if (array[i] > temp[i]) return false;
    return true;
}

std::vector<std::string> Solution::wordSubsets(std::vector<std::string>& words1, std::vector<std::string>& words2) {
    int array[26] = {0};
    for (std::string &word: words2) {
        int temp[26] = {0};
        for (char &c: word)
            temp[c-'a']++;
        for (int i = 0; i < 26; i++)
            array[i] = std::max(array[i], temp[i]);
    }
    
    std::vector<std::string> result;
    for (std::string word: words1)
        if (this->isSubset(word, array))
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