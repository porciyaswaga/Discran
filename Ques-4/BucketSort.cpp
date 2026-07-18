#include <iostream>
#include <forward_list>
#include <vector>


bool Compare(const double& a, const double& b) {
    return a < b;
}

void BucketSort(std::forward_list<double>& data, int size) {
    if (data.empty()) return;

    double minVal = data.front();
    double maxVal = data.front();

    for (double val : data) {
        if (minVal > val) minVal = val;
        if (maxVal < val) maxVal = val;
    }

    if (minVal == maxVal) return;

    int numOfBuckets = size;

    std::vector<std::forward_list<double>> buckets(numOfBuckets);

    for (double val : data) {
        int bucketIndex = static_cast<int>((val - minVal) / (maxVal - minVal) * (numOfBuckets - 1));
        buckets[bucketIndex].push_front(val);
    }

    for (auto& bucket : buckets) bucket.sort(Compare);

    std::forward_list<double> result;
    auto tail = result.before_begin();

    for (auto& bucket : buckets) {
        for (const auto& val : bucket) {
            tail = result.insert_after(tail, val);
        }
    }

    data = std::move(result);
}

int main() {
    double num;
    std::forward_list<double> data;
    auto tail = data.before_begin();
    int size = 0;

    while (std::cin >> num) {

        tail = data.insert_after(tail, num);
        ++size;
    }

    std::cout << "Size: " << size << '\n';
    std::cout << "Before sorting: \n";
    for (const auto& num : data) {
        std::cout << num << ' ';
    }
    std::cout << '\n';

    BucketSort(data, size);

    std::cout << "After sorting:\n";
    for (const auto& num : data) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}
