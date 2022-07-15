#include <vector>
#include <stack>
#include <unordered_map>
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
    std::unordered_map<int, int> mymap;
    int index;
    TreeNode* helper(std::vector<int> &preorder, int start, int end);
public:
    TreeNode* buildTree(std::vector<int> &preorder, std::vector<int> &inorder);
};

TreeNode* Solution::helper(std::vector<int> &preorder, int start, int end) {
    if (start > end) return nullptr;
    const int value = preorder[this->index++];
    TreeNode *node = new TreeNode(value);
    node->left = this->helper(preorder, start, this->mymap[value]-1);
    node->right = this->helper(preorder, this->mymap[value]+1, end);
    return node;
}

TreeNode* Solution::buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    for (int i = 0; i < inorder.size(); i++) {
        const int value = inorder[i];
        this->mymap[value] = i;
    }
    this->index = 0;
    return this->helper(preorder, 0, inorder.size()-1);
}

void free(TreeNode *node) {
    if (node == nullptr) return;
    free(node->left);
    free(node->right);
    delete node;
}

std::vector<int> Preorder(TreeNode *head) {
    if (head == nullptr) return {};
    std::vector<int> result;
    std::stack<TreeNode*> stk;
    stk.push(head);
    while (!stk.empty()) {
        TreeNode *node = stk.top(); stk.pop();
        result.push_back(node->val);
        if (node->right != nullptr) stk.push(node->right);
        if (node->left != nullptr) stk.push(node->left);
    }
    return result;
}

std::vector<int> Inorder(TreeNode *head) {
    if (head == nullptr) return {};
    std::vector<int> result;
    std::stack<TreeNode*> stk;
    TreeNode *cur = head;
    while (cur != nullptr || !stk.empty()) {
        if (cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
            continue;
        }
        TreeNode *node = stk.top(); stk.pop();
        result.push_back(node->val);
        cur = node->right;
    }
    return result;
}

TEST(TestBuildTreeSuite, TestBuildTree) {
    std::vector<int> preorder{3,9,20,15,7};
    std::vector<int> inorder{9,3,15,20,7};

    Solution solution = Solution();
    TreeNode *node = solution.buildTree(preorder, inorder);

    std::vector<int> wantPreorder = Preorder(node);
    std::vector<int> wantInorder = Inorder(node);

    ASSERT_EQ(wantPreorder.size(), preorder.size());
    ASSERT_EQ(wantInorder.size(), inorder.size());

    for (int i = 0; i < preorder.size(); i++) {
        EXPECT_EQ(wantPreorder[i], preorder[i]);
        EXPECT_EQ(wantInorder[i], inorder[i]);
    }

    free(node);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}