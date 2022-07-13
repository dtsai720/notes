#include <vector>
#include <queue>
#include <iostream>

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
    std::vector<std::vector<int>> levelOrder(TreeNode* root);
};

std::vector<std::vector<int>> Solution::levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> output;
    if (root == nullptr) return output;
    std::queue<TreeNode*> q;
    q.push(root);
    std::vector<int> current;
    while (!q.empty()) {
        current.clear();
        size_t size = q.size();
        while (size-- > 0) {
            TreeNode* node = q.front(); q.pop();
            current.push_back(node->val);
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        output.push_back(current);
    }
    return output;
}

void free(TreeNode *node) {
    if (node == nullptr) return;
    free(node->left);
    free(node->right);
    delete node;
}

int main(int argc, char **argv) {
    TreeNode *node = new TreeNode(3);
    TreeNode *cur = node;
    cur->left = new TreeNode(9);
    cur->right = new TreeNode(20);
    cur = cur->right;
    cur->left = new TreeNode(15);
    cur->right = new TreeNode(7);

    Solution solution = Solution();
    auto result = solution.levelOrder(node);
    for (auto& nums: result) {
        for (int num: nums) {
            std::cout << num << std::endl;
        }
        std::cout << std::endl;
    }
    free(node);
    return 0;
}