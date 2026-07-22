#include <iostream>
#include <string>
#include <vector>

struct Point {
    int key;
    Point* left;
    Point* right;
};

Point* FindMin(Point* node) {
    if (node == nullptr) return nullptr;
    while(node->left != nullptr) {
        node = node->left;
    }
    return node;
}

bool Search(Point*& head, int num) {
    if (head == nullptr) return false;
    if (num < head->key) return Search(head->left, num);
    if (num > head->key) return Search(head->right, num);
    return true;
}

void AddPoint(Point*& head, int num) {
    if (head == nullptr) {
        head = new Point();
        head->left = nullptr;
        head->right = nullptr;
        head->key = num;
        return;
    }
    if (head->key > num) AddPoint(head->left, num);
    if (head->key < num) AddPoint(head->right, num);
}

bool DeletePoint(Point*& head, int num) {
    if (head == nullptr) return false;
    if (num < head->key) return DeletePoint(head->left, num);
    if (num > head->key) return DeletePoint(head->right, num);

    Point* temp = head;

    if (head->left == nullptr && head->right == nullptr) {
        delete head;
        head = nullptr;
    } else if (head->left == nullptr) {
        head = head->right;
        delete temp;
    } else if (head->right == nullptr) {
        head = head->left;
        delete temp;
    } else {
        Point* minNode = FindMin(head->right);
        head->key = minNode->key;
        DeletePoint(head->right, minNode->key);
    }
    return true;
}

void PrintTree(Point* head, int level = 0) {
    if (head == nullptr) return;
    PrintTree(head->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    std::cout << head->key << std::endl;
    PrintTree(head->left, level + 1);
}

void DeleteTree(Point*& head) {
    if (head == nullptr) return;
    DeleteTree(head->left);
    DeleteTree(head->right);
    delete head;
    head = nullptr;
}

void InorderTreeWalk(Point* head) {
    if (head == nullptr) return;
    InorderTreeWalk(head->left);
    std::cout << head->key << " ";
    InorderTreeWalk(head->right);
}

int TreeMax(Point* head) {
    if (head == nullptr) return -1;
    while (head->right != nullptr) {
        head = head->right;
    }
    return head->key;
}

int TreeMin(Point* head) {
    if (head == nullptr) return -1;
    while (head->left != nullptr) {
        head = head->left;
    }
    return head->key;
}

int main() {
    Point* root = nullptr;
    
    AddPoint(root, 10);
    AddPoint(root, 5);
    AddPoint(root, 15);
    AddPoint(root, 3);
    AddPoint(root, 7);
    AddPoint(root, 12);
    AddPoint(root, 18);
    
    std::cout << "Дерево:" << std::endl;
    PrintTree(root);
    
    std::cout << "\nПоиск 7: " << (Search(root, 7) ? "найден" : "не найден") << std::endl;
    std::cout << "Поиск 99: " << (Search(root, 99) ? "найден" : "не найден") << std::endl;
    
    std::cout << "\nУдаляем 5..." << std::endl;
    DeletePoint(root, 5);
    PrintTree(root);
    
    std::cout << "\nУдаляем 10..." << std::endl;
    DeletePoint(root, 10);
    PrintTree(root);
    
    std::cout << "\nInorder обход: ";
    InorderTreeWalk(root);
    std::cout << std::endl;
    
    std::cout << "Min: " << TreeMin(root) << std::endl;
    std::cout << "Max: " << TreeMax(root) << std::endl;
    
    DeleteTree(root);
    
    return 0;
}
