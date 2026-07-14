#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


void CountingSortByDigit(std::vector<int>& A, int exp) {
    const int BASE = 10;
    std::vector<int> C(BASE, 0);
    std::vector<int> B(A.size());

    for (int i = 0; i < A.size(); ++i) {
        int digit = (A[i] / exp) % BASE;
        C[digit]++;
    }

    for (int i = 1; i < BASE; ++i) {
        C[i] += C[i - 1];
    }

    for (int i = A.size() - 1; i >= 0; --i) {
        int digit = (A[i] / exp) % BASE;
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    for (int i = 0; i < B.size(); ++i) {
        A[i] = B[i];
    }
}

void RadixSort(std::vector<int>& data) {
    if (data.empty()) return;

    int maxNum = data[0];
    for (const auto& num : data) {
        if (num > maxNum) {
            maxNum = num;
        }
    }
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        CountingSortByDigit(data, exp);
    }
}


int main() {
    std::vector<int> data;
    int num;
    std::cout << "Input num (Use Ctrl+D to stop)\n";
    while (std::cin >> num) data.push_back(num);

    std::cout << "Data: ";
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';

    RadixSort(data);

    std::cout << "Sorted Data: ";
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';
}
