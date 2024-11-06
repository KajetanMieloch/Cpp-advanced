#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
void as_sorted_view(const std::vector<T>& vec) {
    std::vector<T> sorted_vec = vec;
    std::sort(sorted_vec.begin(), sorted_vec.end());
    for (const auto& elem : sorted_vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    as_sorted_view(vec);
    //original vector is not sorted
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    return 0;
}