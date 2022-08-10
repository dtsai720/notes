#include <vector>
#include <queue>
#include <gtest/gtest.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    std::vector<TreeNode*> array;
    void traversal(TreeNode* root);
public:
    void flatten(TreeNode* root);
};

void Solution::traversal(TreeNode* root) {
    if (root == nullptr) return;
    this->array.push_back(root);
    this->traversal(root->left);
    this->traversal(root->right);
}

void Solution::flatten(TreeNode* root) {
    if (root == nullptr) return;
    this->traversal(root);
    for (int i = 0; i < this->array.size()-1; i++) {
        this->array[i]->left = nullptr;
        this->array[i]->right = this->array[i+1];
    }
}

TEST(TestFlatternSuite, TestFlattern) {
    TreeNode *head = new TreeNode(1);
    head->left = new TreeNode(2);
    head->left->left = new TreeNode(3);
    head->left->right = new TreeNode(4);
    head->right = new TreeNode(5);
    head->right->right = new TreeNode(6);

    Solution solution = Solution();
    solution.flatten(head);

    std::vector<int> want{1,2,3,4,5,6};
    TreeNode *cur = head;
    int idx = 0;
    while (cur != nullptr) {
        ASSERT_EQ(cur->val, want[idx++]);
        ASSERT_EQ(cur->left, nullptr);
        cur = cur->right;
    }
    ASSERT_EQ(idx, want.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}