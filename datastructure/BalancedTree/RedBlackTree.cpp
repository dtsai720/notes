#include <string>

#define RED true;
#define BLACK false;

/*
1. Each node is red or black.
2. Root is black.
3. Leaf node(nil) is black.
4. If the node is red, its children's nodes are black.
5. On any node, there must be the same number of black nodes 
   that go from the node to the path of any descendant leaf.

*/

struct TreeNode {
    int Value;
    bool Color;
    TreeNode *Left;
    TreeNode *Right;
    TreeNode() : Value(0), Left(nullptr), Right(nullptr), Color(false) {}
    TreeNode(int x) : Value(x), Left(nullptr), Right(nullptr), Color(false) {}
    TreeNode(int x, TreeNode *Left, TreeNode *Right) : Value(x), Left(Left), Right(Right), Color(false) {}
};

class RedBlackTree {
private:
    TreeNode *Root;
public:
    void LeftRotate(TreeNode *x);
    void RightRotate(TreeNode *x);
};

inline void RedBlackTree::LeftRotate(TreeNode *x) {
    TreeNode *y = x->Right;
    x->Right = y->Left;
    if (y->Left != this->Nil)
        y->Left->Parent = x;

    y->Parent = x->Parent;
    if (x->Parent == this->Nil)
        this->Root = y;
    else if (x == x->Parent->Left)
        x->Parent->Left = y;
    else
        x->Parent->Right = y;

    y->Left = x;
    x->Parent = y;
}

inline void RedBlackTree::RightRotate(TreeNode *y) {
    TreeNode *x = y->Left;
    y->Left = x->Right;
    if (x->Right != this->Nil)
        x->Right->Parent = y;

    x->Parent = y->Parent;
    if (x->Parent == this->Nil)
        this->Root = x;
    else if (y == y->Parent->Left)
        y->Parent->Left = x;
    else
        y->Parent->Right = x;
    
    x->Right = y;
    y->Parent = x;
}

int main(int argc, char **argv) {
    return 0;
}