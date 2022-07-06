# include <gtest/gtest.h>

class Node {

private:
    int height() { return this == nullptr? 0: 1+std::max(this->Left->height(), this->Right->height()); }
    Node *RR() {
        Node *node = this->Right;
        this->Right = node->Left;
        node->Left = this;
        return node;
    }
    Node *LL() {
        Node *node = this->Left;
        this->Left = node->Right;
        node->Right = this;
        return node;
    }
    Node *LR() {
        Node *node = this->Left;
        this->Left = node->RR();
        return this->LL();
    }
    Node *RL() {
        Node *node = this->Right;
        this->Right = node->LL();
        return this->RR();
    }

public:
    int Value;
    Node *Left, *Right;

    Node(int value) { this->Value = value; }
    int difference() { return this->Left->height() - this->Right->height(); }
    Node *nodeWithMimumValue() {
        Node *cur;
        for (cur = this; cur->Left != nullptr; cur = cur->Left);
        return cur;
    }
    Node *balance() {
        int bf = this->difference();
        if (-1 <= bf && bf <= 1) return this;
        if (bf > 1) {
            return this->Left->difference() > 0? this->LL(): this->LR();
        }
        return this->Right->difference() > 0? this->RL(): this->RR();
    }
};

class AVLTree {

public:
    Node *insert(Node *root, int value) {
        if (root == nullptr) return new Node(value); 
        if (root->Value > value)
            root->Left = insert(root->Left, value);
        else
            root->Right = insert(root->Right, value);
        return root->balance();
    }
    Node *deleteNode(Node *root, int value) {
        if (root == nullptr) return nullptr;
        if (root->Value > value)
            root->Left = deleteNode(root->Left, value);
        else if (root->Value < value)
            root->Right = deleteNode(root->Right, value);
        else if (root->Left == nullptr)
            return root->Right;
        else if (root->Right == nullptr) {
            return root->Left;
        } else {
            Node *temp = root->Right->nodeWithMimumValue();
            root->Value = temp->Value;
            root->Right = deleteNode(root->Right, temp->Value);
        }
        return root->balance();
    }
};

TEST(TestAVLTree, AVLTree) {
    Node *root = new Node(0);
    AVLTree solution = AVLTree();
    for (int i = 1; i < (1 << 4) - 1; i++)
        root = solution.insert(root, i);
    ASSERT_EQ(root->difference(), 0);
    delete(root);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}