#include <iostream>
#include <memory>

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

int main() {
    BinarySearchTree<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(2);
    bst.insert(7);

    std::cout << "In-order traversal: ";
    bst.print_in_order();
    std::cout << std::endl;

    return 0;
}
