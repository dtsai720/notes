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
public:
    std::vector<int> rightSideView(TreeNode *root);
};

std::vector<int> Solution::rightSideView(TreeNode *root) {
    std::vector<int> output;
    if (root == nullptr) return output;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        size_t size = q.size();
        output.push_back(q.back()->val);
        while (size-- > 0) {
            TreeNode* node = q.front(); q.pop();
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
    }
    return output;
}

void free(TreeNode *node) {
    if (node == nullptr) return;
    free(node->left);
    free(node->right);
    delete node;
}

TEST(TestRightSideViewSuite, TestRightSideViewNormal) {
    TreeNode *node = new TreeNode(1);
    TreeNode *cur = node;
    cur->left = new TreeNode(2);
    cur->left->right = new TreeNode(5);
    cur->right = new TreeNode(3);
    cur->right->right = new TreeNode(4);

    Solution solution = Solution();
    std::vector<int> want{1, 3, 4};
    std::vector<int> result = solution.rightSideView(node);

    ASSERT_EQ(want.size(), result.size());
    for (int i = 0; i < want.size(); i++)
        EXPECT_EQ(want[i], result[i]);
    free(node);
}

TEST(TestRightSideViewSuite, TestRightSideViewNullptr) {
    Solution solution = Solution();
    std::vector<int> want{};
    std::vector<int> result = solution.rightSideView(nullptr);

    ASSERT_EQ(want.size(), result.size());
    for (int i = 0; i < want.size(); i++)
        EXPECT_EQ(want[i], result[i]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}