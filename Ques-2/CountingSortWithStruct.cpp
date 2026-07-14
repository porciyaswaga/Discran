#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


struct Human {
    int age;
    std::string name;
};


void CountingSort(std::vector<Human>& A) {
    int n = 0;
    for (const auto& human : A) {
        if (human.age > n) {
            n = human.age;
        }
    }
    std::vector<int> C(n + 1, 0);
    std::vector<Human> B(A.size());
    for (int i = 0; i < A.size(); ++i) {
        C[A[i].age]++; 
    }
    for (int i = 1; i <= n; ++i) {
        C[i] += C[i - 1];
    }
    for (int i = A.size() - 1; i >= 0; --i) {
        B[C[A[i].age] - 1] = A[i];
        C[A[i].age]--;
    }
    for (int i = 0; i < B.size(); ++i) {
        A[i] = B[i];
    }
}

int main() {
    Human human;
    std::vector<Human> data;
    while (true) {
        std::cout << "Input name (or stop): ";
        std::cin >> human.name;

        if (human.name == "stop") {
            break;
        }

        std::cout << "Input age: ";
        std::cin >> human.age;

        data.push_back(human);
    }
        std::cout << "Size of Human list " << data.size() << '\n';

        for (const auto& hum : data) {
            std::cout << "Name: " << hum.name << "; "
                      << "Age: " << hum.age << '\n';
        }

    std::cout << '\n';
    
    CountingSort(data);

    for (const auto& hum : data) {
        std::cout << "Name: " << hum.name << "; "
                  << "Age: " << hum.age << '\n';
    }
}
