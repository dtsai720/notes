#include <vector>
#include <iostream>
#include <gtest/gtest.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right);
};

ListNode* Solution::reverseBetween(ListNode* head, int left, int right) {
    if (left == right || head == nullptr) return head;
    ListNode *cur = head, *prev = nullptr;
    for (int i = 1; i < left; i++) {
        prev = cur;
        cur = cur->next;
    }
    ListNode *start = prev, *tail = cur, *next = nullptr;
    for (int i = left; i <= right; i++) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    tail->next = cur;
    if (left > 1)
        start->next = prev;
    else
        head = prev;
    return head;
}

ListNode* ToLinkedList(std::vector<int> nums) {
    ListNode *head = new ListNode(-1);
    ListNode *cur = head;
    for (int num: nums) {
        cur->next = new ListNode(num);
        cur = cur->next;
    }
    return head->next;
}

std::vector<int> ToVector(ListNode *head) {
    ListNode *cur = head;
    std::vector<int> result;
    while (cur != nullptr) {
        result.push_back(cur->val);
        cur = cur->next;
    }
    return result;
}

TEST(TestReverseBetweenSuite, TestReverseBetween1) {
    Solution solution = Solution();
    ListNode *head = ToLinkedList({1,2,3,4,5});
    ListNode *result = solution.reverseBetween(head,2,4);
    std::vector<int> want{1,4,3,2,5};
    std::vector<int> actual = ToVector(result);
    ASSERT_EQ(want, actual);
}

TEST(TestReverseBetweenSuite, TestReverseBetween2) {
    Solution solution = Solution();
    ListNode *head = ToLinkedList({5});
    ListNode *result = solution.reverseBetween(head,1,1);
    std::vector<int> want{5};
    std::vector<int> actual = ToVector(result);
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}