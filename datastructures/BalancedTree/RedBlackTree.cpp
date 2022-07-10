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

class TreeNode {

public:
    bool Color;
    int Value;
    TreeNode *Left, *Right, *Parent;
    TreeNode(int value) {
        this->Value = value;
        this->Left = nullptr;
        this->Right = nullptr;
    }
};

/*
============================================================
   P                            P
   |        Left Rotate         |
   X        ---------->         Y
  / \                          / \
 a   Y      Right Rotate      X    c
    / \     <-----------     / \
   b   c                    a   b
============================================================
InsertFixedCase:
A: new Node
============================================================
1. CaseI: A, X, Y is red. Z is Black, current is A
   => A, Z is red, X, Y is black, current move to Z

   W                       W
   |                       |
   Z                       Z
  / \                     / \
 X   Y    ---------->    X   Y
  \                       \
   A                       A
============================================================
2. CaseII: A, X is red, Y, Z is black, current is A
   => A, Z is red, X is black

     W                                W
     |                                |
     Z                                X
    / \     A, X, Z Right Rotate     / \
   X   Y    ------------------->    A   Z
  / \                                  / \
 A   c                                c   Y
============================================================
3. CaseIII: A, X is red, Y, X is black, current is A

   W                              W                W
   |                              |                |
   Z                              Z                A
  / \     A, X Left Rotate       /     CaseII     / \
 X   Y    --------------->      A      ----->    X   Z
  \                            /                    / \
   A                          X                    c   Y
============================================================
*/

class RedBlackTree {

private:
    TreeNode *Root;
    void LeftRotate(TreeNode *x);
    void RightRotate(TreeNode *x);
    void FixedUpInsert(TreeNode *current);
public:
    void Insert(int value);
};

inline void RedBlackTree::LeftRotate(TreeNode *x) {
    TreeNode *y = x->Right;
    x->Right = y->Left;
    if (y->Left != nullptr)
        y->Left->Parent = x;

    y->Parent = x->Parent;
    if (x->Parent == nullptr)
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
    if (x->Right != nullptr)
        x->Right->Parent = y;

    x->Parent = y->Parent;
    if (x->Parent == nullptr)
        this->Root = x;
    else if (y == y->Parent->Left)
        y->Parent->Left = x;
    else
        y->Parent->Right = x;
    
    x->Right = y;
    y->Parent = x;
}

inline void RedBlackTree::Insert(int value) {
    TreeNode *node = new TreeNode(value);
    TreeNode *cur = this->Root;
    TreeNode *parent = nullptr;
    while (cur != nullptr) {
        parent = cur;
        cur = cur->Value > value? cur->Right: cur->Left;
    }
    node->Parent = parent;
    if (parent == nullptr)
        this->Root = node;
    else if (value > parent->Value)
        parent->Right = node;
    else
        parent->Left = node;
    // Default color is red.
    node->Color = RED;
    this->FixedUpInsert(node);
}

inline void RedBlackTree::FixedUpInsert(TreeNode *current) {
    // Continue RED
    while (current->Parent->Color == RED) {
        if (current->Parent == current->Parent->Parent->Left) {
            TreeNode *y = current->Parent->Parent->Right;
            if (y->Color == RED) {
                current->Parent->Color = BLACK;
                y->Color = BLACK;
                current->Parent->Parent->Color = RED;
                current = current->Parent->Parent;
            } else {
                if (current == current->Parent->Right) {
                    current = current->Parent;
                    this->LeftRotate(current);
                }
                current->Parent->Color = BLACK;
                current->Parent->Parent->Color = RED;
                this->RightRotate(current->Parent->Parent);
            }
        } else {
            TreeNode *y = current->Parent->Parent->Left;
            if (y->Color == RED) {
                current->Parent->Color = BLACK;
                y->Color = BLACK;
                current->Parent->Parent->Color = RED;
                current = current->Parent->Parent;
            } else {
                if (current == current->Parent->Left) {
                    current = current->Parent;
                    this->RightRotate(current);
                }
                current->Parent->Color = BLACK;
                current->Parent->Parent->Color = RED;
                this->LeftRotate(current->Parent->Parent);
            }
        }
    }
    this->Root->Color = BLACK;
}

int main(int argc, char **argv) {
    return 0;
}