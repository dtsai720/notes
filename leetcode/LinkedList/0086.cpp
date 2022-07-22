#include <vector>
#include <gtest/gtest.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

class Solution {
public:
    ListNode* partition(ListNode* head, int x);
};

ListNode* Solution::partition(ListNode *head, int x) {
    ListNode *greater = new ListNode(-1), *less = new ListNode(-1);
    ListNode *g_cur = greater, *l_cur = less;
    for (; head != nullptr; head = head->next) {
        if (head->val >= x) {
            g_cur->next = head;
            g_cur = g_cur->next;
        } else {
            l_cur->next = head;
            l_cur = l_cur->next;
        }
    }
    g_cur->next = nullptr;
    l_cur->next = greater->next;
    return less->next;
}

TEST(TestPartitionSuite, TestPartition) {
    ListNode *head = ToLinkedList({1,4,3,2,5,2});
    Solution solution = Solution();
    ListNode *actual = solution.partition(head, 3);
    std::vector<int> want{1,2,2,4,3,5};
    ASSERT_EQ(want, ToVector(actual));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}