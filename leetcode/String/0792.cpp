#include <string>
#include <map>
#include <gtest/gtest.h>

class Trie {
public:
    char c;
    Trie *next;
    Trie(char c) {
        this->c = c;
        this->next = nullptr;
    }
};

class Solution {
private:
    std::map<std::pair<Trie*, std::string>, bool> mymap;
    bool isSubseq(Trie *head, std::string s);
public:
    int numMatchingSubseq(std::string s, std::vector<std::string> words);
};

bool Solution::isSubseq(Trie *head, std::string s) {
    if (this->mymap.count({head, s}) > 0) return this->mymap[{head, s}];
    Trie *cur = head;
    int idx = 0;
    while (cur != nullptr && idx < s.length()) {
        if (cur->c == s[idx]) idx++;
        cur = cur->next;
    }
    return this->mymap[{head, s}] = idx == s.length();
}

int Solution::numMatchingSubseq(std::string s, std::vector<std::string> words) {
    int result = 0;
    Trie *root = new Trie('-');
    Trie *cur = root;
    for (char &c: s) {
        cur->next = new Trie(c);
        cur = cur->next;
    }
    for (std::string word: words) result += this->isSubseq(root, word);
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