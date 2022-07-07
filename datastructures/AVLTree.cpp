#include <gtest/gtest.h>
#include <queue>
#include <stdlib.h>

/*
abs(RightHeight - LeftHeight) <= 1

   P                            P
   |        Left Rotate         |
   X        ---------->         Y
  / \                          / \
 a   Y      Right Rotate      X    c
    / \     <-----------     / \
   b   c                    a   b

Left Right Rotate:
   P                         P                        P
   |                         |                        |
   Z                         Z                        Y
  /     X Left Rotate       /     Z Right Rotate     / \
 X      ------------>      Y      ------------->    X   Z
  \                       /
   Y                     X

Right Left Rotate:
 P                        P                           P
 |                        |                           |
 Z                        Z                           Y
  \     X Right Rotate     \       Z Left Rotate     / \
   X    ------------->      Y      ------------>    Z   X
  /                          \
 Y                            X

*/
class TreeNode {

public:
    int value;
    TreeNode *left, *right;
    TreeNode(int value) { this->value = value; }
};

class AVLTree {
private:
    int height(TreeNode* node);
    TreeNode *LeftRotate(TreeNode *x);
    TreeNode *RightRotate(TreeNode *y);
    TreeNode *LeftRightRotate(TreeNode *node);
    TreeNode *RightLeftRotate(TreeNode *node);

public:
    TreeNode *insert(TreeNode *root, int value);
    TreeNode *deleteNode(TreeNode *root, int value);
    TreeNode *minValueNode(TreeNode *root);
    TreeNode *balance(TreeNode *node);
    int difference(TreeNode *node);
    void show(TreeNode *root);
};

inline TreeNode *AVLTree::LeftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
inline TreeNode *AVLTree::RightRotate(TreeNode *y) {
    TreeNode *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}
inline TreeNode *AVLTree::LeftRightRotate(TreeNode *z) {
    TreeNode *x = z->left;
    z->left = this->LeftRotate(x);
    return this->RightRotate(z);
}
inline TreeNode *AVLTree::RightLeftRotate(TreeNode *z) {
    TreeNode *x = z->right;
    z->right = this->RightLeftRotate(x);
    return this->LeftRotate(z);
}
inline int AVLTree::height(TreeNode *node) {
    return node == nullptr? 0:
        1+std::max(this->height(node->left), this->height(node->right));
}
inline int AVLTree::difference(TreeNode *node) {
    return this->height(node->left) - this->height(node->right);
}
inline TreeNode *AVLTree::insert(TreeNode *root, int value) {
    if (root == nullptr)
        return new TreeNode(value);
    if (root->value > value)
        root->left = this->insert(root->left, value);
    else
        root->right = this->insert(root->right, value);
    return this->balance(root);
}
inline TreeNode *AVLTree::deleteNode(TreeNode *root, int value) {
    if (root == nullptr)
        return nullptr;
    if (root->value > value)
        root->left = this->deleteNode(root->left, value);
    else if (root->value < value)
        root->right = this->deleteNode(root->right, value);
    else if (root->left == nullptr)
        return root->right;
    else if (root->right == nullptr) {
        return root->left;
    } else {
        TreeNode *temp = this->minValueNode(root->right);
        root->value = temp->value;
        root->right = this->deleteNode(root->right, temp->value);
    }
    return this->balance(root);
}
inline TreeNode *AVLTree::minValueNode(TreeNode *root) {
    TreeNode *cur;
    for (cur = root; cur->left != nullptr; cur = cur->left);
    return cur;
}
inline TreeNode *AVLTree::balance(TreeNode *root) {
    int bf = this->difference(root);
    if (std::abs(bf) <= 1)
        return root;
    if (bf > 1)
        return this->difference(root->left) > 0? this->RightRotate(root): this->RightLeftRotate(root);
    return this->difference(root->right) > 0? this->LeftRightRotate(root): this->LeftRotate(root);
}
inline void AVLTree::show(TreeNode *root) {
    if (root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        std::cout << node->value << std::endl;
        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }
}

TEST(TestAVLTree, AVLTree) {
    TreeNode *root = new TreeNode(0);
    AVLTree solution = AVLTree();
    for (int i = 1; i < (1 << 4) - 1; i++)
        root = solution.insert(root, i);
    ASSERT_EQ(solution.difference(root), 0);
    delete(root);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}