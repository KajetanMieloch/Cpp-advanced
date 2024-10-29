#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>

bool naturalOrderCompare(const std::string& a, const std::string& b)
{
    int i = 0, j = 0;
    while (i < a.size() && j < b.size())
    {
        if (std::isdigit(a[i]) && std::isdigit(b[j]))
        {
            int num1 = 0, num2 = 0;
            while (i < a.size() && std::isdigit(a[i]))
            {
                num1 = num1 * 10 + (a[i] - '0');
                i++;
            }
            while (j < b.size() && std::isdigit(b[j]))
            {
                num2 = num2 * 10 + (b[j] - '0');
                j++;
            }
            if (num1 != num2)
            {
                return num1 < num2;
            }
        }
        else
        {
            if (a[i] != b[j])
            {
                return a[i] < b[j];
            }
            i++;
            j++;
        }
    }
    return a.size() < b.size();
}

template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type 
insertionSort(std::vector<T>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && naturalOrderCompare(key, arr[j]))
        {
            arr.at(j + 1) = arr[j];
            j -= 1;
        }
        arr.at(j + 1) = key;
    }
}

template<int N>
struct factorial
{
    static const int value = N * factorial<N - 1>::value;
};


template<>
struct factorial<0>
{
    static const int value = 1;
};

template<typename T>
void print_all(T t) {
    std::cout << t << " ";
}

template<typename T, typename... Args>
void print_all(T t, Args... args) {
    std::cout << t << " ";
    print_all(args...);
}



int main()
{
    std::vector<std::string> arr3 = {"zad1", "das1", "zad2", "zad7", "zad11"};
    insertionSort(arr3);
    std::vector<std::string> stdsortarr3 = arr3;
    std::sort(stdsortarr3.begin(), stdsortarr3.end());
    std::cout << "Natural order compare: " << std::endl;
    for (auto& l : arr3)
    {
        std::cout << l << " ";
    }
    std::cout << std::endl;
    std::cout << "std::sort: " << std::endl;
    for (auto& l : stdsortarr3)
    {
        std::cout << l << " ";
    }

    std::cout << std::endl;

    std::vector<std::string> arr4 = {"zad2ab", "zad1ba"};
    insertionSort(arr4);
    for (auto& l : arr4)
    {
        std::cout << l << " ";
    }

    std::cout << std::endl;

    std::cout << factorial<5>::value << std::endl;
    std::cout << factorial<0>::value << std::endl;
    std::cout << std::endl;


    print_all(1, 1.0, 1.0f, "Hello");
    std::cout<<" "<<std::endl;
    print_all(1, 2.0);
    std::cout<<" "<<std::endl;

    return 0;
}