#include <iostream>
#include <string>
#include <algorithm>

struct Node {
    std::string key;
    int bit;
    Node* left;
    Node* right;
};

int GetBit(const std::string& key, int bit) {
    int ByteIndex = bit / 8;
    int BitIndex = 7 - (bit % 8);

    return (key[ByteIndex] >> BitIndex) & 1;
}

bool IsForward(Node* current, Node* next) {
    return next->bit > current->bit;
}

Node* CreateNode(const std::string& key, int bit) {
    Node* node = new Node();

    node->key = key;
    node->bit = bit;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

int FirstDifferentBit(const std::string& a, const std::string& b) {
    int maxBits = std::min(a.size(), b.size()) * 8;

    for (int bit = 0; bit < maxBits; ++bit) {
        if (GetBit(a, bit) != GetBit(b, bit)) {
            return bit;
        }
    }

    return -1;
}

Node* Search(Node* header, const std::string& key) {
    Node* current = header->left;

    while (true) {
        int bit = GetBit(current->key, current->bit);

        Node* next;

        if (bit == 0)
            next = current->left;
        else
            next = current->right;

        if (IsForward(current, next))
            current = next;
        else
            break;
    }

    return current;
}

void Insert(Node*& header, const std::string& key) {

    if (header == nullptr) {

        header = new Node();

        header->key = "";
        header->bit = -1;
        header->left = nullptr;
        header->right = nullptr;

        Node* node = new Node();

        node->key = key;
        node->bit = 0;

        node->left = node;
        node->right = header;

        header->left = node;

        return;
    }

    Node* searched = Search(header, key);

    if (searched->key == key)
        return;

    int b = FirstDifferentBit(searched->key, key);

    Node* node = new Node();

    node->key = key;
    node->bit = b;

    Node* parent = header;
    Node* current = header->left;

    while (current->bit < b) {

        parent = current;

        int bit = GetBit(key, current->bit);

        if (bit == 0)
            current = current->left;
        else
            current = current->right;
    }

    if (parent == header) {
        header->left = node;
    }
    else {
        int bit = GetBit(key, parent->bit);

        if (bit == 0)
            parent->left = node;
        else
            parent->right = node;
    }

    int newBit = GetBit(key, b);

    if (newBit == 0) {
        node->left = node;
        node->right = current;
    }
    else {
        node->left = current;
        node->right = node;
    }
}


int main() {

    Node* header = nullptr;

    Insert(header, "car");
    Insert(header, "cat");
    Insert(header, "dog");

    std::string word = "dog";

    Node* result = Search(header, word);

    std::cout << (result->key == word) << '\n';

    return 0;
}
