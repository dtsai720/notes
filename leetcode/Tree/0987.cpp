#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

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
    unordered_map<int, unordered_map<int, vector<int>>> mymap;
    void set_map(TreeNode* root, int x, int y);
public:
    vector<vector<int>> verticalTraversal(TreeNode* root);
};

void Solution::set_map(TreeNode* root, int x, int y) {
    if (root == nullptr) return;
    mymap[x][y].push_back(root->val);
    if (root->left != nullptr) this->set_map(root->left, x-1, y+1);
    if (root->right != nullptr) this->set_map(root->right, x+1, y+1);
}

vector<vector<int>> Solution::verticalTraversal(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;

    this->mymap.clear();
    this->set_map(root, 0, 0);

    vector<int> keys;
    for (auto& key: this->mymap) keys.push_back(key.first);
    sort(keys.begin(), keys.end());

    for (const int x: keys) {
        vector<int> nums;
        for (auto& num: this->mymap[x]) nums.push_back(num.first);
        sort(nums.begin(), nums.end());

        vector<int> array;
        for (const int y: nums) {
            vector<int> arr = this->mymap[x][y];
            sort(arr.begin(), arr.end());
            array.insert(array.end(), arr.begin(), arr.end());
        }
        result.push_back(array);
    }
    return result;
}

int main(int argc, char **argv) {
    return 0;
}