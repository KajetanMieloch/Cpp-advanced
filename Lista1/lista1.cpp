#include <iostream>
#include <vector>
#include <string>

//Zad1
template<typename T, typename C>
T my_max(T a, T b, C comp)
{
    return comp(a,b);
}

//Zad2
template<typename T>
void insertionSort(std::vector<T>& arr)
{
    //insertion sort for vector
    for(int i = 1; i < arr.size(); i++)
    {
        T key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr.at(j+1) = arr[j];
            j -= 1;
        }
        arr.at(j+1) = key;
    }
}

//Zad3
namespace cpplab
{
    template<typename T>
    class vector
    {
        private:
        T data;
        std::size_t a;
        
    };
}

int main()
{   
    //Zad1
    std::cout << "Lista 1, Kajetan Mieloch" << std::endl << "=========================" << std::endl;
    std::cout << "Zad 1" << std::endl << "=========================" << std::endl;
    std::cout << my_max(4, 3, [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max(4.3, 3.4, [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max("AAA", "ZZZ", [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max("ZZZ", "AAA", [] (auto a, auto b) { return a < b ? b : a; }) << std::endl;
    std::cout << my_max('a', 'z', [] (auto a, auto b) { return a > b ? b : a; }) << std::endl;
    std::cout << "Zad 2" << std::endl << "=========================" << std::endl;
    

    //Zad2
    std::vector<int> intvec = {12, 11, 13, 5, 6};
    std::vector<std::string> stringvec = {"a", "c", "b", "d"};
    insertionSort(intvec);
    insertionSort(stringvec);
    for (auto &l:intvec)
    {
        std::cout<<l<<" ";
    }
    std::cout<<std::endl;
    for (auto &l:stringvec)
    {
        std::cout<<l<<" ";
    }
    std::cout<<std::endl;
    

    return 0;
}