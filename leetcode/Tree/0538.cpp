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
    void helper(TreeNode *root, int &cur);
public:
    TreeNode* convertBST(TreeNode *root);
};

void Solution::helper(TreeNode *root, int &cur) {
    if (root == nullptr) return;
    this->helper(root->right, cur);
    cur += root->val;
    root->val = cur;
    this->helper(root->left, cur);
}

TreeNode* Solution::convertBST(TreeNode *root) {
    int cur = 0;
    this->helper(root, cur);
    return root;
}

bool ValidBST(TreeNode *root) {
    if (root == nullptr) return true;
    if (root->right != nullptr && root->right->val > root->val) return false;
    if (root->left != nullptr && root->left->val < root->val) return false;
    return ValidBST(root->left) && ValidBST(root->right);
}

void free(TreeNode *node) {
    if (node == nullptr) return;
    free(node->left);
    free(node->right);
    delete node;
}

TEST(TestCovertBSTSuite, TestCovertBST) {
    Solution solution = Solution();
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(3);
    root->right = new TreeNode(6);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    root->right->right->right = new TreeNode(8);
    solution.convertBST(root);

    ASSERT_TRUE(ValidBST(root));
    free(root);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}