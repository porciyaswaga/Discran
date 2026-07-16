#include <iostream>
#include <forward_list>
#include <string>
#include <vector>

struct Human {
    double weight;
    std::string name;
};

bool Compare(const Human& a, const Human& b) {
    return a.weight < b.weight;
}

void BucketSort(std::forward_list<Human>& data, int size) {
    if (data.empty()) return;

    double maxWeight = data.front().weight;
    double minWeight = data.front().weight;

    for (const auto& human : data) {
        if (maxWeight < human.weight) maxWeight = human.weight;
        if (minWeight > human.weight) minWeight = human.weight;
    }

    std::vector<std::forward_list<Human>> buckets(size);

    for (const auto& human : data) {
        size_t index = (human.weight - minWeight) * size /
                       (maxWeight - minWeight + 1);
        buckets[index].push_front(human);
    }

    for (auto& bucket : buckets)
        bucket.sort(Compare);

    std::forward_list<Human> result;
    auto tail = result.before_begin();

    for (auto& bucket : buckets) {
        for (const auto& human : bucket) {
            tail = result.insert_after(tail, human);
        }
    }

    data = std::move(result);
}

int main() {
    Human human;
    std::forward_list<Human> data;
    auto tail = data.before_begin();
    int size = 0;

    while (true) {
        std::cout << "Input name (or stop): ";
        std::cin >> human.name;

        if (human.name == "stop") break;

        std::cout << "Input weight (centners): ";
        std::cin >> human.weight;

        tail = data.insert_after(tail, human);
        ++size;
    }

    std::cout << "Size: " << size << '\n';

    std::cout << "Before sorting:\n";
    for (const auto& human : data) {
        std::cout << "Name: " << human.name
                  << " Weight: " << human.weight << '\n';
    }

    BucketSort(data, size);

    std::cout << "\nAfter sorting:\n";
    for (const auto& human : data) {
        std::cout << "Name: " << human.name
                  << " Weight: " << human.weight << '\n';
    }
}
