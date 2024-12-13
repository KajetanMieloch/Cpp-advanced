#include <iostream>
#include <vector>
#include <random>
#include <thread>


std::random_device rd;
std::mt19937 gen(rd());

std::vector<int> v;

void populate_and_shuffle_vector(std::vector<int> &v, int n){
    for(int i = 0; i < n; i++){
        v.push_back(i);
    }

    for(int i = 0; i < n; i++){
        std::uniform_int_distribution<> dis(0, n-1);
        int random_index = dis(gen);
        std::swap(v[i], v[random_index]);
    }

}

void quicksort(std::vector<int> &v, int left, int right){
    if(left < right){
        int pivot = v[(left+right)/2];
        int i = left;
        int j = right;

        while(i <= j){
            while(v[i] < pivot){
                i++;
            }

            while(v[j] > pivot){
                j--;
            }

            if(i <= j){
                std::swap(v[i], v[j]);
                i++;
                j--;
            }
        }

        std::thread t1(quicksort, std::ref(v), left, j);
        std::thread t2(quicksort, std::ref(v), i, right);

        t1.join();
        t2.join();
    }
}

int main(){

    populate_and_shuffle_vector(v, 10);

    std:

    for(auto i : v){
        std::cout << i << " ";
    }

    std::cout << std::endl;

    quicksort(v, 0, v.size()-1);

    for(auto i : v){
        std::cout << i << " ";
    }

    std::cout << std::endl;

    return 0;
}
