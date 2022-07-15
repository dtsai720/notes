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

struct TreeNode {
    int Value;
    TreeNode *Left;
    TreeNode *Right;
    TreeNode() : Value(0), Left(nullptr), Right(nullptr) {}
    TreeNode(int x) : Value(x), Left(nullptr), Right(nullptr) {}
    TreeNode(int x, TreeNode *Left, TreeNode *Right) : Value(x), Left(Left), Right(Right) {}
};

class AVLTree {
private:
    int Height(TreeNode* node);
    TreeNode *LeftRotate(TreeNode *x);
    TreeNode *RightRotate(TreeNode *y);
    TreeNode *LeftRightRotate(TreeNode *node);
    TreeNode *RightLeftRotate(TreeNode *node);
    TreeNode *Balance(TreeNode *node);
    TreeNode *MinValueNode(TreeNode *root);
public:
    TreeNode *InsertNode(TreeNode *root, int value);
    TreeNode *DeleteNode(TreeNode *root, int value);
    int Difference(TreeNode *node);
};

inline TreeNode *AVLTree::LeftRotate(TreeNode *x) {
    TreeNode *y = x->Right;
    x->Right = y->Left;
    y->Left = x;
    return y;
}

inline TreeNode *AVLTree::RightRotate(TreeNode *y) {
    TreeNode *x = y->Left;
    y->Left = x->Right;
    x->Right = y;
    return x;
}

inline TreeNode *AVLTree::LeftRightRotate(TreeNode *z) {
    TreeNode *x = z->Left;
    z->Left = this->LeftRotate(x);
    return this->RightRotate(z);
}

inline TreeNode *AVLTree::RightLeftRotate(TreeNode *z) {
    TreeNode *x = z->Right;
    z->Right = this->RightLeftRotate(x);
    return this->LeftRotate(z);
}

inline int AVLTree::Height(TreeNode *node) {
    return node == nullptr? 0:
        1+std::max(this->Height(node->Left), this->Height(node->Right));
}

inline int AVLTree::Difference(TreeNode *node) {
    return this->Height(node->Left) - this->Height(node->Right);
}

inline TreeNode *AVLTree::InsertNode(TreeNode *root, int value) {
    if (root == nullptr)
        return new TreeNode(value);
    if (root->Value > value)
        root->Left = this->InsertNode(root->Left, value);
    else
        root->Right = this->InsertNode(root->Right, value);
    return this->Balance(root);
}

inline TreeNode *AVLTree::DeleteNode(TreeNode *root, int value) {
    if (root == nullptr)
        return nullptr;
    if (root->Value > value)
        root->Left = this->DeleteNode(root->Left, value);
    else if (root->Value < value)
        root->Right = this->DeleteNode(root->Right, value);
    else if (root->Left == nullptr)
        return root->Right;
    else if (root->Right == nullptr) {
        return root->Left;
    } else {
        TreeNode *temp = this->MinValueNode(root->Right);
        root->Value = temp->Value;
        root->Right = this->DeleteNode(root->Right, temp->Value);
    }
    return this->Balance(root);
}

inline TreeNode *AVLTree::MinValueNode(TreeNode *root) {
    TreeNode *cur;
    for (cur = root; cur->Left != nullptr; cur = cur->Left);
    return cur;
}

inline TreeNode *AVLTree::Balance(TreeNode *root) {
    int bf = this->Difference(root);
    if (std::abs(bf) <= 1)
        return root;
    if (bf > 1)
        return this->Difference(root->Left) > 0? this->RightRotate(root): this->RightLeftRotate(root);
    return this->Difference(root->Right) > 0? this->LeftRightRotate(root): this->LeftRotate(root);
}

void Show(TreeNode *root) {
    if (root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        std::cout << node->Value << std::endl;
        if (node->Left != nullptr) q.push(node->Left);
        if (node->Right != nullptr) q.push(node->Right);
    }
}

void free(TreeNode *root) {
    if (root == nullptr) return;
    free(root->Left);
    free(root->Right);
    delete(root);
}

TEST(TestAVLTree, AVLTree) {
    TreeNode *root = new TreeNode(0);
    AVLTree solution = AVLTree();
    for (int i = 1; i <= INT8_MAX; i++) {
        root = solution.InsertNode(root, i);
        const int difference = std::abs(solution.Difference(root));
        ASSERT_TRUE(difference <= 1);
    }
    free(root);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}