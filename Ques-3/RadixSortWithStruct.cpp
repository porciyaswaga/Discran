#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


struct Human {
    int age;
    std::string name;
};


void CountingSortByDigit(std::vector<Human>& A, int exp) {
    if (A.empty()) return;

    const int BASE = 10; //десятичная система счисления
    std::vector<int> C(BASE, 0);
    std::vector<Human> B(A.size());

    for (int i = 0; i < A.size(); ++i) {
        int digit = (A[i].age / exp) % BASE;
        C[digit]++;
    }

    for (int i = 1; i < BASE; ++i) {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = A.size() - 1; i >= 0; --i) {
        int digit = (A[i].age / exp) % BASE;
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    for (int i = 0; i < B.size(); ++i) {
        A[i] = B[i];
    }
}

void RadixSort(std::vector<Human>& data) {
    if (data.empty()) return;

    int maxAge = data[0].age;
    for (const auto& human : data) {
        if (human.age > maxAge) {
            maxAge = human.age;
        }
    }
    for (int exp = 1; maxAge / exp > 0; exp *= 10) {
        CountingSortByDigit(data, exp);
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
    
    RadixSort(data);

    for (const auto& hum : data) {
        std::cout << "Name: " << hum.name << "; "
                  << "Age: " << hum.age << '\n';
    }
}
