#include <iostream>
#include <vector>

template<typename T, typename C>
T my_max(T a, T b, C comp)
{
    return comp(a,b);
}

template<typename T>
void insertionSort(std::vector<T>& arr)
{
    //insertion sort for vector
    for(int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr.at(j+1) = arr[j];
            j -= 1;
        }
        arr.at(j+1) = key;
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
    
    std::cout << "Before sorting: ";
    std::vector<int> arr = {12, 11, 13, 5, 6};

    for (auto &l:arr)
    {
        std::cout<<l<<" ";
    }
    std::cout << std::endl;
    insertionSort(arr);
    std::cout << "After sorting: ";
    for (auto &l:arr)
    {
        std::cout<<l<<" ";
    }
    std::cout << std::endl;
    

    return 0;
}