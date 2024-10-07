#include <iostream>

template<typename T, typename C>
T my_max(T a, T b, C comp)
{
    return comp(a,b);
}

template<typename T>
void insertionSort(T arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    std::cout << "Lista 1, Kajetan Mieloch" << std::endl << "=========================" << std::endl;
    std::cout << "Zad 1" << std::endl << "=========================" << std::endl;
    std::cout << my_max(4, 3, [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max(4.3, 3.4, [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max("AAA", "ZZZ", [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max("ZZZ", "AAA", [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max('a', 'z', [] (auto a, auto b) { return a > b ? b : a; }) << std::endl;
    std::cout << "Zad 2" << std::endl << "=========================" << std::endl;
    

    return 0;
}