#include <iostream>
#include <memory>
#include <utility>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <algorithm>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;

        Node(T val, Node* par = nullptr) : value(val), parent(par) {}
    };

    std::unique_ptr<Node> root;

public:
    BinarySearchTree() = default;

    void insert(const T& value) {
        if (!root) {
            root = std::make_unique<Node>(value);
            return;
        }

        Node* current = root.get();
        while (true) {
            if (value < current->value) {
                if (current->left) {
                    current = current->left.get();
                } else {
                    current->left = std::make_unique<Node>(value, current);
                    break;
                }
            } else {
                if (current->right) {
                    current = current->right.get();
                } else {
                    current->right = std::make_unique<Node>(value, current);
                    break;
                }
            }
        }
    }

    void print_in_order() const {
        print_in_order(root.get());
    }

private:
    void print_in_order(const Node* node) const {
        if (!node) return;

        print_in_order(node->left.get());
        std::cout << node->value << " ";
        print_in_order(node->right.get());
    }
};

namespace cpplab {

template<typename T>
class unique_ptr {
private:
    T* ptr;

public:
    explicit unique_ptr(T* ptr = nullptr) : ptr(ptr) {}

    ~unique_ptr() {
        delete ptr;
    }

    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    T* get() const { return ptr; }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* new_ptr = nullptr) {
        delete ptr;
        ptr = new_ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const { return ptr; }

    explicit operator bool() const { return ptr != nullptr; }
};
}

template<typename T>
class non0_ptr {
    static_assert(!std::is_null_pointer_v<T>, "non0_ptr cannot be used with nullptr type");

private:
    T* ptr;

public:
    explicit non0_ptr(T* ptr) : ptr(ptr) {
        if (ptr == nullptr) {
            throw std::invalid_argument("non0_ptr cannot be initialized with nullptr");
        }
    }

    T* get() const { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }

    explicit operator bool() const { return true; }

    non0_ptr() = delete;
};

int knapsack(int N, int W, const std::vector<int>& weights, const std::vector<int>& values) {
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    std::cout << "DP Table:" << std::endl;
    for (int i = 0; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            std::cout << dp[i][w] << " ";
        }
        std::cout << std::endl;
    }

    return dp[N][W];
}

int main() {
    try {
        BinarySearchTree<int> bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(2);
        bst.insert(7);
        std::cout << "In-order traversal: ";
        bst.print_in_order();
        std::cout << std::endl;

        cpplab::unique_ptr<int> uptr(new int(42));
        std::cout << *uptr << std::endl;
        uptr.reset(new int(84));
        std::cout << *uptr << std::endl;
        cpplab::unique_ptr<int> moved = std::move(uptr);
        if (!uptr) {
            std::cout << "null" << std::endl;
        }
        std::cout << *moved << std::endl;
        non0_ptr<int> n0ptr(new int(7));
        std::cout << *n0ptr << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // Liczba skarbów
    int N = 5;

    // Maksymalna nośność
    int W = 10;

    // Wagi skarbów
    std::vector<int> weights = {2, 3, 4, 5, 9};

    // Ceny skarbów
    std::vector<int> values = {3, 4, 8, 8, 10};

    std::cout << "Max value: " << knapsack(N, W, weights, values) << std::endl;

    return 0;
}