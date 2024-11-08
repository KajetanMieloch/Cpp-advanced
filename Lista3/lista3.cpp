#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>  // Dla std::unique_ptr

// zad 2
template <typename T>
void as_sorted_view(std::vector<T> vec) {
    std::sort(vec.begin(), vec.end());
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T>
struct Node
{
    T data;
    std::unique_ptr<Node<T>> next;  // Zmieniamy next na unique_ptr

    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class forward_list
{
public:
    forward_list() : head(nullptr) {}

    // Dodawanie elementu na początek listy
    void push_front(T data)
    {
        auto new_node = std::make_unique<Node<T>>(data); // Tworzymy nowy węzeł
        new_node->next = std::move(head);  // Przenosimy obecny head do new_node->next
        head = std::move(new_node);        // ustawiamy nowy head na nowy węzeł
    }

    // Funkcja wypisująca listę
    void print() const
    {
        Node<T>* temp = head.get();  // Używamy .get() aby uzyskać wskaźnik do węzła
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";  // Wypisujemy dane węzła
            temp = temp->next.get();  // Przechodzimy do następnego węzła
        }
        std::cout << std::endl;
    }

private:
    std::unique_ptr<Node<T>> head;  // Początek listy
};

int main() {

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
    list.print();  // Wypisujemy listę

    return 0;
}
