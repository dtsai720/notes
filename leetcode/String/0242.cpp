#include <string>
#include <gtest/gtest.h>

class Solution {
public:
    bool isAnagram(std::string s, std::string t);
};

bool Solution::isAnagram(std::string s, std::string t) {
    int array[26] = {0};
    for (char &c: s) array[c-'a']++;
    for (char &c: t) array[c-'a']--;
    for (int i = 0; i < 26; i++)
        if (array[i] != 0) return false;
    return true;
}

TEST(TestIsAngramSuite, TestIsAngram) {
    Solution solution = Solution();
    ASSERT_TRUE(solution.isAnagram("anagram", "nagaram"));
    ASSERT_FALSE(solution.isAnagram("rat", "car"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}