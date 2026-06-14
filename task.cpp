#include <iostream>

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

    Node* addNode(Node* root, T value) {
        if (root == nullptr) {
            root = new Node;
            root->value = value;
            root->count = 1;
            root->left = root->right = nullptr;
        } else if (root->value > value) {
            root->left = addNode(root->left, value);
        } else if (root->value < value) {
            root->right = addNode(root->right, value);
        } else {
            root->count++;
        }
        return root;
    }

    void printTree(Node* root) {
        if (root == nullptr) {
            return;
        }
        printTree(root->left);
        for (int i = 0; i < root->count; i++) {
            std::cout << root->value << "->";
        }
        printTree(root->right);
    }

    Node* searchNode(Node* root, T value) {
        if (root == nullptr || root->value == value) {
            return root;
        }
        if (value < root->value) {
            return searchNode(root->left, value);
        } else {
            return searchNode(root->right, value);
        }
    }

    void clear(Node *node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BTS() : root(nullptr) {}

    void add(T value) {
        root = addNode(root, value);
    }

    bool search(T value) {
        return searchNode(root, value) != nullptr;
    }

    void print() {
        printTree(root);
        std::cout << std::endl;
    }

    ~BTS() {
        clear(root);
    }
};

int main () {
    BTS<int> tree;
    
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(11);
    tree.add(3);

    tree.print();


    std::cout << "search(5): " << tree.search(5) << std::endl;
    std::cout << "search(7): " << tree.search(7) << std::endl;

    return 0;
}