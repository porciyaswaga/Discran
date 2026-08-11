#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>

struct Node {
    int value;
    int size;
    int priority;
    Node* left;
    Node* right;
};

int PriorityGenerator() {
    return rand();
}

int Size(Node* node) {
    if (!node)
        return 0;

    return node->size;
}

void UpdateSize(Node* node) {
    if (node)
        node->size = 1 + Size(node->left) + Size(node->right);
}

Node* Merge(Node* LeftTree, Node* RightTree) {
    if (!LeftTree) return RightTree;
    if (!RightTree) return LeftTree;

    if (LeftTree->priority > RightTree->priority) {
        LeftTree->right = Merge(LeftTree->right, RightTree);
        UpdateSize(LeftTree);
        return LeftTree;
    } else {
        RightTree->left = Merge(RightTree->left, LeftTree);
        UpdateSize(RightTree);
        return RightTree;
    }
}

std::pair<Node*, Node*> Split(Node* node, int pos) {
    if (!node)
        return {nullptr, nullptr};

    if (Size(node->left) >= pos) {
        auto [leftTree, rightTree] = Split(node->left, pos);

        node->left = rightTree;
        UpdateSize(node);

        return {leftTree, node};
    } else {
        auto [leftTree, rightTree] =
            Split(node->right, pos - Size(node->left) - 1);

        node->right = leftTree;
        UpdateSize(node);

        return {node, rightTree};
    }
}

Node* Insert(Node* node, int value, int pos) {
    auto [T1, T2] = Split(node, pos);

    Node* newNode = new Node();

    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->priority = PriorityGenerator();
    newNode->size = 1;

    return Merge(Merge(T1, newNode), T2);
}

Node* Delete(Node* node, int pos) {
    auto [left, right] = Split(node, pos);
    auto [deleted, after] = Split(right, 1);

    delete deleted;

    return Merge(left, after);
}

void Print(Node* node) {
    if (!node)
        return;

    Print(node->left);
    std::cout << node->value << ' ';
    Print(node->right);
}

void DeleteTree(Node* node) {
    if (!node)
        return;

    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

int main() {
    srand(time(nullptr));

    Node* root = nullptr;

    root = Insert(root, 10, 0);
    root = Insert(root, 20, 1);
    root = Insert(root, 30, 2);
    root = Insert(root, 40, 3);
    root = Insert(root, 50, 4);

    Print(root);
    std::cout << '\n';

    root = Insert(root, 25, 2);

    Print(root);
    std::cout << '\n';

    root = Delete(root, 2);

    Print(root);
    std::cout << '\n';

    root = Delete(root, 0);

    Print(root);
    std::cout << '\n';

    root = Delete(root, Size(root) - 1);

    Print(root);
    std::cout << '\n';

    DeleteTree(root);

    return 0;
}
