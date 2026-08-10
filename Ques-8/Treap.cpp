#include <iostream>
#include <cstdlib>
#include <utility>

using namespace std;

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
};

int PriorityGenerator() {
    return rand();
}

pair<Node*, Node*> Split(Node* node, int key) {
    if (!node)
        return {nullptr, nullptr};

    if (node->key <= key) {
        auto [leftPart, rightPart] = Split(node->right, key);
        node->right = leftPart;
        return {node, rightPart};
    }

    if (node->key > key) {
        auto [leftPart, rightPart] = Split(node->left, key);
        node->left = rightPart;
        return {leftPart, node};
    }

    return {nullptr, nullptr};
}

Node* Merge(Node* LeftTree, Node* RightTree) {
    if (!LeftTree)
        return RightTree;

    if (!RightTree)
        return LeftTree;

    if (LeftTree->priority > RightTree->priority) {
        LeftTree->right = Merge(LeftTree->right, RightTree);
        return LeftTree;
    } else {
        RightTree->left = Merge(RightTree->left, LeftTree);
        return RightTree;
    }
}

Node* Insert(Node* node, int key) {
    auto [T1, T2] = Split(node, key);

    Node* newNode = new Node();
    newNode->key = key;
    newNode->priority = PriorityGenerator();
    newNode->left = nullptr;
    newNode->right = nullptr;

    Node* T1_ = Merge(T1, newNode);
    Node* T = Merge(T1_, T2);

    return T;
}

void Clear(Node* node) {
    if (!node) return;

    Clear(node->left);
    Clear(node->right);

    delete node;
}

Node* Delete(Node* node, int key) {
    auto [T1, T2] = Split(node, key);
    auto [T1_, T2_] = Split(T1, key - 1);

    Clear(T2_);

    return Merge(T1_, T2);
}

void Print(Node* node, int depth = 0) {
    if (!node)
        return;

    Print(node->right, depth + 1);

    for (int i = 0; i < depth; i++)
        cout << "    ";

    cout << node->key << "(" << node->priority << ")" << "\n";

    Print(node->left, depth + 1);
}

int main() {
    srand(42);

    Node* root = nullptr;

    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 30);
    root = Insert(root, 5);
    root = Insert(root, 15);
    root = Insert(root, 25);
    root = Insert(root, 40);

    cout << "Treap:\n";
    Print(root);

    root = Delete(root, 25);

    cout << "\nAfter delete 25:\n";
    Print(root);

    root = Delete(root, 10);

    cout << "\nAfter delete 10:\n";
    Print(root);

    root = Delete(root, 30);

    cout << "\nAfter delete 30:\n";
    Print(root);

    return 0;
}
