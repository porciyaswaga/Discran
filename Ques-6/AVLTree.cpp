#include <iostream>
#include <string>
#include <algorithm>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int Height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

Node* FindMin(Node* node) {
    if (node == nullptr) return nullptr;
    while(node->left != nullptr) node = node->left;
    return node;
}

Node*& Search(Node*& head, int num) {
    if (head == nullptr) return head;
    if (num < head->key) return Search(head->left, num);
    if (num > head->key) return Search(head->right, num);
    return head;
}

Node* RightRotate(Node* y) {
    Node* x = y->left;
    Node* z = x->right;

    x->right = y;
    y->left = z;

    y->height = 1 + std::max(Height(y->left), Height(y->right));
    x->height = 1 + std::max(Height(x->left), Height(x->right));

    return x;
}

Node* LeftRotate(Node* x) {
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    y->height = 1 + std::max(Height(y->left), Height(y->right));
    x->height = 1 + std::max(Height(x->left), Height(x->right));

    return y;
}

int BF(Node* node) {
    if (node == nullptr) return 0;
    else return Height(node->left) - Height(node->right);
}

Node* Balance(Node* node) {
    int bf = BF(node);

    if (bf > 1 && BF(node->left) >= 0) return RightRotate(node);
    if (bf < -1 && BF(node->right) <= 0) return LeftRotate(node); 
    if (bf > 1 && BF(node->left) < 0) {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }
    if (bf < -1 && BF(node->right) > 0) {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }
    return node;
}

Node* Insert(Node*& head, int num) {
    if (head == nullptr) {
        Node* newNode = new Node();
        newNode->key = num;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (head->key > num) head->left = Insert(head->left, num);
    else if (head->key < num) head->right = Insert(head->right, num);
    else return head;

    head->height = 1 + std::max(Height(head->left), Height(head->right));
    return Balance(head);
}

void Delete(Node*& head, int num) {
    if (head == nullptr) return;
    if (head->key > num) {
        Delete(head->left, num);
    }
    else if (head->key < num) {
        Delete(head->right, num);
    }
    else {
    Node* temp = head;
    
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
            Node* minNode = FindMin(head->right);
            head->key = minNode->key;
            Delete(head->right, minNode->key);
        }
    }
    if (head == nullptr) return;
    head->height = 1 + std::max(Height(head->left), Height(head->right));
    head = Balance(head);
}

int main() {
    Node* root = nullptr;

    Insert(root, 10);
    Insert(root, 5);
    Insert(root, 15);
    Insert(root, 3);
    Insert(root, 7);
    Insert(root, 12);
    Insert(root, 18);
    Insert(root, 1);
    Insert(root, 4);
    Insert(root, 6);
    Insert(root, 8);

    std::cout << "Поиск 7: ";
    if (Search(root, 7) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    std::cout << "Поиск 100: ";
    if (Search(root, 100) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    std::cout << "\nУдаляем лист (1)\n";
    Delete(root, 1);

    std::cout << "Поиск 1: ";
    if (Search(root, 1) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    std::cout << "\nУдаляем узел с одним ребенком (3)\n";
    Delete(root, 3);

    std::cout << "Поиск 3: ";
    if (Search(root, 3) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    std::cout << "\nУдаляем узел с двумя детьми (5)\n";
    Delete(root, 5);

    std::cout << "Поиск 5: ";
    if (Search(root, 5) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    std::cout << "\nУдаляем корень (10)\n";
    Delete(root, 10);

    std::cout << "Поиск 10: ";
    if (Search(root, 10) != nullptr)
        std::cout << "найден\n";
    else
        std::cout << "не найден\n";

    Node* minNode = FindMin(root);
    if (minNode != nullptr)
        std::cout << "\nМинимальный элемент: " << minNode->key << '\n';

    return 0;
}
