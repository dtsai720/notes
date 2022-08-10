#include <vector>
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
    TreeNode* build(std::vector<int>& nums, int start, int end);
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums);
};

TreeNode* Solution::build(std::vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start+end) /2;
    TreeNode *node = new TreeNode(nums[mid]);
    node->left = this->build(nums, start, mid-1);
    node->right = this->build(nums, mid+1, end);
    return node;
}

TreeNode* Solution::sortedArrayToBST(std::vector<int>& nums) {
    return this->build(nums, 0, nums.size()-1);
}

int main(int argc, char **argv) {
    return 0;
}