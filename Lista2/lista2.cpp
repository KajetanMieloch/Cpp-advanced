#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type 
insertionSort(std::vector<T>& arr)
{
    std::cout << "This is a string" << std::endl;
}

template<typename T>
typename std::enable_if<!std::is_same<T, std::string>::value, void>::type 
insertionSort(std::vector<T>& arr)
{
    std::cout << "This is not a string" << std::endl;
}

int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6};
    insertionSort(arr);

    std::cout << std::endl;

    std::vector<std::string> arr2 = {"Ala", "ma", "kota", "a", "kot", "ma", "Ale"};
    insertionSort(arr2);

    return 0;
}
