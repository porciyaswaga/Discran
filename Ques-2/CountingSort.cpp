#include <iostream>
#include <vector>

void CountingSort(std::vector<int>& A) {
    int n = 0;
    for (const auto& num : A) {
        if (num > n) n = num;
    }
    
    std::vector<int> C(n + 1, 0);
    std::vector<int> B(A.size());
    
    for (int i = 0; i < A.size(); ++i) C[A[i]]++;
    for (int i = 1; i <= n; ++i) C[i] += C[i - 1];
    for (int i = A.size() - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
    for (int i = 0; i < B.size(); ++i) A[i] = B[i];
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

    CountingSort(data);

    std::cout << "Sorted Data: \n";
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';
}
