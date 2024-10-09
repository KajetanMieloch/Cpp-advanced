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
        T* vdata;
        std::size_t vsize;
        typedef T value_type;

        public:
        T* begin() {return vdata;}
        T* end() {return vdata + vsize;}

        T& operator[](std::size_t index)
        {
            return vdata[index];
        }

        void operator=(std::vector<T> stdvector)
        {
            vsize = stdvector.size();
            for(int i = 0; i < stdvector.size(); i++)
            {
                vdata[i] = stdvector[i];
            }
        }

        vector(std::size_t size = 0)
        {
            vdata = new T[size];
            vsize = size;
        }

        std::size_t get_size()
        {
            return vsize;
        }

        void insert_data(int indx, T data)
        {
            T* temp = new T[vsize + 1];
            for(int i = 0; i < indx; i++)
            {
                temp[i] = vdata[i];
            }
            temp[indx] = data;
            for(int i = indx; i < vsize; i++)
            {
                temp[i+1] = vdata[i];
            }
            delete[] vdata;
            vdata = temp;
            vsize++;
        }

        void erase_data(int indx)
        {
            T* temp = new T[vsize - 1];
            for(int i = 0; i < indx; i++)
            {
                temp[i] = vdata[i];
            }
            for(int i = indx; i < vsize - 1; i++)
            {
                temp[i] = vdata[i+1];
            }
            delete[] vdata;
            vdata = temp;
            vsize--;
        }

        void shorten_vec(int newsize)
        {
            T* temp = new T[newsize];
            for(int i = 0; i < newsize; i++)
            {
                temp[i] = vdata[i];
            }
            delete[] vdata;
            vdata = temp;
            vsize = newsize;
        }

        T dot_product(std::vector<T> stdvector)
        {
            std::cout << stdvector.size() << std::endl;
            std::cout << vsize << std::endl;

            if (vsize == 0 || stdvector.size() == 0)
                {
                    return 0;
                }

            std::cout << value_type << std::endl;

            if (stdvector.size() == vsize)
            {
                T sum = 0;
                for(int i = 0; i < vsize; i++)
                {
                    sum += vdata[i] * stdvector[i];
                }
                return sum;
            }
            else
            {
                return 0;
            }
        }

        ~vector()
        {
            delete[] vdata;
            vdata = nullptr;
        }
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
    
    //Zad3
    std::cout << "Zad 3" << std::endl << "=========================" << std::endl;
    cpplab::vector<int> vec(5);
    vec[0] = 1;
    vec[1] = 2;
    vec.insert_data(1, 3);
    vec.erase_data(0);
    vec.shorten_vec(2);
    for(int i = 0; i < vec.get_size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }

    cpplab::vector<int> cppvector;
    cppvector = {1, 2, 3, 4, 5};
    std::vector<int> stdvector = {1, 2, 3, 4, 5};
    std::cout << cppvector.dot_product(stdvector) << std::endl;

}