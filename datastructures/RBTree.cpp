#include <string>

#define RED true;
#define Black false;

/*
1. Each node is red or black.
2. Root is black.
3. Leaf node(nil) is black.
4. If the node is red, its children's nodes are black.
5. On any node, there must be the same number of black nodes 
   that go from the node to the path of any descendant leaf.

*/

class TreeNode {
public:
    bool color;
    int value;
    TreeNode *left, *right, *parent;

    TreeNode(int value) {
        this->value = value;
    }
};


class RedBlackTree {
private:
    TreeNode *root, *neel;
public:
    void LeftRotate(TreeNode *x);
    void RightRotate(TreeNode *x);
};

inline void RedBlackTree::LeftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left != this->neel)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == this->neel)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

inline void RedBlackTree::RightRotate(TreeNode *y) {
    TreeNode *x = y->left;
    y->left = x->right;
    if (x->right != this->neel)
        x->right->parent = y;

    x->parent = y->parent;
    if (x->parent == this->neel)
        this->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

int main(int argc, char **argv) {
    return 0;
}