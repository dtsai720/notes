#include <vector>

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
    void traversal(TreeNode* root, std::vector<int>& array);
public:
    bool isValidBST(TreeNode* root);
};

void Solution::traversal(TreeNode* root, std::vector<int>& array) {
    if (root == nullptr) return;
    this->traversal(root->left, array);
    array.push_back(root->val);
    this->traversal(root->right, array);
}

bool Solution::isValidBST(TreeNode* root) {
    std::vector<int> array;
    this->traversal(root, array);
    for (int i = 1; i < array.size(); i++)
        if (array[i] <= array[i-1]) return false;
    return true;
}

int main(int argc, char **argv) {
    return 0;
}