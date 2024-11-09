#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>  // Dla std::unique_ptr
#include <stdexcept>
#include <type_traits>
#include <concepts>

template <typename T>
concept Multipliable = requires(T a, T b) {
    { a * b } -> std::same_as<T>;
};

template <typename L, typename C>
concept ScalarMultipliable = requires(L v1, C v2) {
    { v1.size() } -> std::convertible_to<std::size_t>;
    { v2.size() } -> std::convertible_to<std::size_t>;
    { v1[0] * v2[0] } -> Multipliable;
    { v1.size() == v2.size() } -> std::convertible_to<bool>;
    { v1[0] } -> std::same_as<decltype(v2[0])>;
};

template<typename L, typename C>
requires ScalarMultipliable<L, C>
auto operator*(L &v1, C &v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("Vectors must be of the same size.");
    }

    if (v1.size() == 0) {
        throw std::invalid_argument("Vectors must not be empty.");
    }

    using ResultType = decltype(v1[0] * v2[0]);
    ResultType result = 0;
    
    for (std::size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }

    return result;
}


// zad 2
template <typename T>
void as_sorted_view(std::vector<T> vec) {
    std::sort(vec.begin(), vec.end());
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// zad 3
template <typename T>
struct Node
{
    T data;
    std::unique_ptr<Node<T>> next;
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class forward_list
{
public:
    forward_list() : head(nullptr) {}

    void push_front(T data)
    {
        auto new_node = std::make_unique<Node<T>>(data); // Tworzymy nowy węzeł
        new_node->next = std::move(head);  // Przenosimy obecny head do new_node->next
        head = std::move(new_node);        // ustawiamy nowy head na nowy węzeł
    }

    void reverse()
    {
        std::unique_ptr<Node<T>> prev = nullptr;
        std::unique_ptr<Node<T>> current = std::move(head);
        std::unique_ptr<Node<T>> next = nullptr;

        while (current != nullptr)
        {
            next = std::move(current->next);  // Zapisujemy wskaźnik na następny element
            current->next = std::move(prev);  // Odwracamy wskaźnik
            prev = std::move(current);        // Przesuwamy wskaźnik na obecny element
            current = std::move(next);        // Przesuwamy wskaźnik na następny element
        }

        head = std::move(prev);  // Ustawiamy head na ostatni element
    }

    // Funkcja wypisująca listę
    void print() const
    {
        Node<T>* temp = head.get();
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next.get();
        }
        std::cout << std::endl;
    }

private:
    std::unique_ptr<Node<T>> head;
};

int main() {

    // zad 1
    try {
        // Test z wektorami liczb
        std::vector<int> v1 = {1, 2, 3};
        std::vector<int> v2 = {4, 5, 6};
        auto result = v1 * v2;
        std::cout << "Iloczyn skalarny: " << result << std::endl;

        // Test z niezgodnymi rozmiarami
        std::vector<int> v3 = {1, 2, 3};
        std::vector<int> v4 = {4, 5};
        std::cout << v3 * v4;  // Wyjątek

        // Test z nieodpowiednimi typami (std::string)
        std::vector<std::string> v5 = {"Hello", "world"};
        std::vector<std::string> v6 = {"C++", "rocks"};
        //std::cout << v5 * v6;  // Błąd kompilacji, bo nie ma operatora * dla std::string

    } catch (const std::invalid_argument& e) {
        std::cout << "Błąd: " << e.what() << std::endl;
    }

    // zad 2
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    as_sorted_view(vec);

    // Po posortowaniu, oryginalny wektor nie jest posortowany
    for (const auto& elem : vec) {
        std::cout << elem << " ";  // Wypisujemy oryginalny wektor
    }
    std::cout << std::endl;

    // zad 3
    forward_list<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);

    std::cout << "Original list: ";
    list.print();

    list.reverse();
    std::cout << "Reversed list: ";
    list.print();



    return 0;
}
