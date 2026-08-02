#include <iostream>
#include <vector>

struct Node {
    int key;
    char color;
    Node* left;
    Node* right;
    Node* parent;
};

Node NILNode = {0, 'B', nullptr, nullptr, nullptr};
Node* NIL = &NILNode;
Node* root = NIL;

void LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

Node* Search(Node* head, int num) {
    if (head == NIL) return head;
    if (head->key > num) return Search(head->left, num);
    if (head->key < num) return Search(head->right, num);
    return head;
}

void InsertFixUp(Node* node) {
    while (node != root && node->parent->color == 'R') {
        if (node->parent == node->parent->parent->left) {
            Node* GrandParent = node->parent->parent;
            Node* Uncle = GrandParent->right;
            if (Uncle != NIL && Uncle->color == 'R') {
                GrandParent->color = 'R';
                Uncle->color = 'B';
                node->parent->color = 'B';
                node = GrandParent;
            }
            else if (Uncle->color == 'B' && node == node->parent->left) {
                node->parent->color = 'B';
                GrandParent->color = 'R';
                RightRotate(GrandParent);
            }
            else if (Uncle->color == 'B' && node == node->parent->right) {
                node = node->parent;
                LeftRotate(node);
                node->parent->color = 'B';
                GrandParent->color = 'R';
                RightRotate(GrandParent);
            }
        } else if (node->parent == node->parent->parent->right ) {
            Node* GrandParent = node->parent->parent;
            Node* Uncle = GrandParent->left;
            if (Uncle != NIL && Uncle->color == 'R') {
                GrandParent->color = 'R';
                node->parent->color = 'B';
                Uncle->color = 'B';
                node = GrandParent;
            }
            else if (Uncle->color == 'B' && node == node->parent->right) {
                node->parent->color = 'B';
                GrandParent->color = 'R';
                LeftRotate(GrandParent);
            } else if (Uncle->color == 'B' && node == node->parent->left) {
                node = node->parent;
                RightRotate(node);
                node->parent->color = 'B';
                GrandParent->color = 'R';
                LeftRotate(GrandParent);
            }
        }
    }
    root->color = 'B';
}

Node* Insert(Node* head, int num) {
    Node* parent = nullptr;
    while (head != NIL) {
        if (num < head->key) {
            parent = head;
            head = head->left;
        } else if (num > head->key) {
            parent = head;
            head = head->right;
        } else {
            return head;
        }
    }

    Node* newNode = new Node();
    newNode->parent = parent;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->key = num;
    newNode->color = 'R';

    if (parent == nullptr) root = newNode;
    else if (num < parent->key) parent->left = newNode;
    else parent->right = newNode;

    InsertFixUp(newNode);
    return root;
}

Node* TreeMinimum(Node* node) {
    while (node->left != NIL) node = node->left;
    return node;
}

Node* TreeSuccessor(Node* node) {
    if (node->right != NIL) return TreeMinimum(node->right);

    Node* parent = node->parent;

    while(parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void DeleteFixUp(Node* node) {
    while (node != root && node->color == 'B') {
        if (node == node->parent->left) {
            Node* brother = node->parent->right;

            if (brother->color == 'R') {
                brother->color = 'B';
                node->parent->color = 'R';
                LeftRotate(node->parent);
                brother = node->parent->right;
            }

            if (brother->color == 'B' && brother->left->color == 'B' && brother->right->color == 'B') {
                brother->color = 'R';
                node = node->parent;
                continue;
            }

            if (brother->color == 'B' && brother->left->color == 'R' && brother->right->color == 'B') {
                brother->left->color = 'B';
                brother->color = 'R';
                RightRotate(brother);
                brother = node->parent->right;
            }

            if (brother->color == 'B' && brother->right->color == 'R') {
                brother->color = node->parent->color;
                node->parent->color = 'B';
                brother->right->color = 'B';
                LeftRotate(node->parent);
                node = root;
            }
        } else if (node == node->parent->right) {
            Node* brother = node->parent->left;

            if (brother->color == 'R') {
                brother->color = 'B';
                node->parent->color = 'R';
                RightRotate(node->parent);
                brother = node->parent->left;
            }

            if (brother->color == 'B' && brother->right->color == 'B' && brother->right->color == 'B') {
                brother->color = 'R';
                node = node->parent;
                continue;
            }

            if (brother->color == 'B' && brother->right->color == 'R' && brother->left->color == 'B') {
                brother->right->color = 'B';
                brother->color = 'R';
                LeftRotate(brother);
                brother = node->parent->left;
            }

            if (brother->color == 'B' && brother->left->color == 'R') {
                brother->color = node->parent->color;
                node->parent->color = 'B';
                brother->left->color = 'B';
                RightRotate(node->parent);
                node = root;
            }
        }
    }
    node->color = 'B';
}

void Delete(Node* node, int num) {
    while (node != NIL) {
        if (node->key > num) {
            node = node->left;
        } else if (node->key < num) {
            node = node->right;
        } else {
            Node* z = node;
            Node* y;
            Node* x;

            if (z->left == NIL || z->right == NIL)
                y = z;
            else
                y = TreeSuccessor(z);

            if (y->left != NIL)
                x = y->left;
            else
                x = y->right;

            x->parent = y->parent;

            if (y->parent == nullptr)
                root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;

            if (y != z)
                z->key = y->key;

            if (y->color == 'B')
                DeleteFixUp(x);

            delete y;
            return;
        }
    }
}

void InOrderTreeWalk(Node* head) {
    if (head == NIL) return;
    InOrderTreeWalk(head->left);
    std::cout << head->key << ' ';
    InOrderTreeWalk(head->right);
}

void PrintTree(Node* head, int level = 0) {
    if (head == NIL) return;
    PrintTree(head->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    std::cout << head->key << "(" << head->color << ")" << std::endl;
    PrintTree(head->left, level + 1);
}

int main() {
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;

    // ========== ВСТАВКА ==========
    std::cout << "Вставка элементов: 10, 5, 15, 3, 7, 12, 18, 1, 4, 6, 8\n" << std::endl;
    
    root = Insert(root, 10);
    root = Insert(root, 5);
    root = Insert(root, 15);
    root = Insert(root, 3);
    root = Insert(root, 7);
    root = Insert(root, 12);
    root = Insert(root, 18);
    root = Insert(root, 1);
    root = Insert(root, 4);
    root = Insert(root, 6);
    root = Insert(root, 8);

    std::cout << "Дерево после вставки:" << std::endl;
    PrintTree(root);
    std::cout << "\nInorder обход: ";
    InOrderTreeWalk(root);
    std::cout << std::endl << std::endl;

    // ========== ПОИСК ==========
    std::cout << "=== ПОИСК ===" << std::endl;
    std::cout << "Поиск 7: " << (Search(root, 7) != NIL ? "найден" : "не найден") << std::endl;
    std::cout << "Поиск 100: " << (Search(root, 100) != NIL ? "найден" : "не найден") << std::endl;
    std::cout << std::endl;

    // ========== УДАЛЕНИЕ ==========
    std::cout << "=== УДАЛЕНИЕ ===" << std::endl;

    // Тест 1: Удаление листа (1)
    std::cout << "\n1. Удаляем лист (1):" << std::endl;
    Delete(root, 1);
    std::cout << "Inorder после удаления 1: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Тест 2: Удаление узла с одним потомком (3)
    std::cout << "\n2. Удаляем узел с одним потомком (3):" << std::endl;
    Delete(root, 3);
    std::cout << "Inorder после удаления 3: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Тест 3: Удаление узла с двумя потомками (5)
    std::cout << "\n3. Удаляем узел с двумя потомками (5):" << std::endl;
    Delete(root, 5);
    std::cout << "Inorder после удаления 5: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Тест 4: Удаление корня (10)
    std::cout << "\n4. Удаляем корень (10):" << std::endl;
    Delete(root, 10);
    std::cout << "Inorder после удаления 10: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Тест 5: Удаление несуществующего элемента
    std::cout << "\n5. Удаляем несуществующий элемент (99):" << std::endl;
    Delete(root, 99);
    std::cout << "Inorder после попытки удаления 99: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Тест 6: Удаление оставшихся элементов по одному
    std::cout << "\n6. Удаляем оставшиеся элементы:" << std::endl;
    Delete(root, 4);
    std::cout << "После удаления 4: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 6);
    std::cout << "После удаления 6: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 7);
    std::cout << "После удаления 7: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 8);
    std::cout << "После удаления 8: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 12);
    std::cout << "После удаления 12: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 15);
    std::cout << "После удаления 15: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    Delete(root, 18);
    std::cout << "После удаления 18: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;

    // Проверка, что дерево пустое
    std::cout << "\nДерево пустое? " << (root == NIL ? "Да" : "Нет") << std::endl;

    // ========== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ==========
    std::cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << std::endl;

    // Тест 7: Вставка после удаления
    std::cout << "\n7. Вставка после удаления:" << std::endl;
    root = Insert(root, 25);
    root = Insert(root, 20);
    root = Insert(root, 30);
    std::cout << "Вставили 25, 20, 30" << std::endl;
    std::cout << "Inorder обход: ";
    InOrderTreeWalk(root);
    std::cout << std::endl;
    std::cout << "Дерево:" << std::endl;
    PrintTree(root);

    // Тест 8: Удаление всех элементов
    std::cout << "\n8. Удаляем все элементы:" << std::endl;
    Delete(root, 20);
    Delete(root, 25);
    Delete(root, 30);
    std::cout << "После удаления всех: ";
    InOrderTreeWalk(root);
    std::cout << (root == NIL ? " (дерево пусто)" : "") << std::endl;

    std::cout << "\nВсе тесты пройдены!" << std::endl;

    return 0;
}
