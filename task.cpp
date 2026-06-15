#include <iostream>
#include <string>

template <typename T>
class BTS {
private:
    struct Node {
        T value;
        Node *left;
        Node *right;
        int count;
    };

    Node* root;

    Node* addNode(Node* node, T value, T parent, bool isLeft) {
        if (node == nullptr) {
            if (root == nullptr) {
                std::cout << "Корень дерева: " << value << std::endl;
            } else if (isLeft) {
                std::cout << "Левым потомком узла " << parent << " становится " << value << std::endl;
            } else {
                std::cout << "Правым потомком узла " << parent << " становится " << value << std::endl;
            }
            node = new Node;
            node->value = value;
            node->count = 1;
            node->left = node->right = nullptr;
        } else if (node->value > value) {
            node->left = addNode(node->left, value, node->value, true);
        } else if (node->value < value) {
            node->right = addNode(node->right, value, node->value, false);
        } else {
            std::cout << "Узел " << value << " уже существует, count=" << node->count + 1 << std::endl;
            node->count++;
        }
        return node;
    }

    Node* searchNode(Node* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->value == value) {
            return node;
        }

        if (value < node->value)  {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }

 
    void printTree(Node* node, int depth) {
        if (node == nullptr) {
            return;
        }
        printTree(node->right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << "[" << node->value << "]";

        if (node->count > 1) {
            std::cout << " x" << node->count;
        }

        std::cout << "\n";
        printTree(node->left, depth + 1);
    }

    void clear(Node* node) {
        if (node) { 
            clear(node->left); clear(node->right); 
            
            delete node; 
        }
    }

public:
    BTS() : root(nullptr) {}

    void add(T value) {
        root = addNode(root, value, T{}, false);
    }

    bool search(T value) {
        return searchNode(root, value) != nullptr;
    }

    ~BTS() { 
        clear(root); 
    }
};

int main() {
    BTS<int> tree;

    std::cout << std::endl;
    std::cout << "Построение дерева:" << std::endl;
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(11);
    tree.add(3);

    // std::cout << "Поиск:" << std::endl;
    // std::cout << "search(5): " << tree.search(5) << "\n";
    // std::cout << "search(7): " << tree.search(7) << "\n";

    return 0;
}