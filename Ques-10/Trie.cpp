#include <iostream>
#include <string>
#include <vector>


const int K = 26;

struct Vertex {
    Vertex* to[K] = {0};
    bool terminal = 0;
};

Vertex* root = new Vertex();

bool Search(std::string& word) {
    Vertex* v = root;
    for (char c : word) {
        c -= 'a';
        if (!v->to[c]) return false;
        v = v->to[c];
    }
    return v->terminal;
}

void Insert(std::string& word) {
    Vertex* v = root;
    for (char c : word) {
        c -= 'a';
        if (!v->to[c]) v->to[c] = new Vertex();
        v = v->to[c];
    }
    v->terminal = true;
}

bool Delete(std::string& word) {
    Vertex* v = root;
    std::vector<Vertex*> path;
    path.push_back(root);
    for (char c : word) {
        int x = c - 'a';

        if (!v->to[x]) return false;

        v = v->to[x];
        path.push_back(v);
    }

    if (!v->terminal) return false;

    v->terminal = false;
    
    for (int i = word.size(); i > 0; --i) {
        Vertex* cur = path[i];
        bool hasChild = false;

        for (int j = 0; j < 26; ++j) {
            if (cur->to[j]) {
                hasChild = true;
                break;
            }
        }

        if (cur->terminal || hasChild) break;
        
        Vertex* parent = path[i - 1];
        int x = word[i - 1] - 'a';
        
        delete cur;
        parent->to[x] = nullptr;
    }
    
    return true;
}

int main() {
    std::string word;

    Insert(word = "cat");
    Insert(word = "car");
    Insert(word = "cart");
    Insert(word = "dog");

    std::cout << Search(word = "cat") << '\n';
    std::cout << Search(word = "car") << '\n';
    std::cout << Search(word = "cart") << '\n';
    std::cout << Search(word = "dog") << '\n';
    std::cout << Search(word = "cow") << '\n';

    std::cout << Delete(word = "cat") << '\n';

    std::cout << Search(word = "cat") << '\n';
    std::cout << Search(word = "car") << '\n';
    std::cout << Search(word = "cart") << '\n';

    std::cout << Delete(word = "car") << '\n';

    std::cout << Search(word = "car") << '\n';
    std::cout << Search(word = "cart") << '\n';

    std::cout << Delete(word = "hello") << '\n';

    return 0;
}
