//
// Created by Kirill Smetankin on 15/11/2018.
//

#include <iostream>

template <class T>
struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
};

template <class T>
class Bin_tree {
 public:
    void add(T val);
 private:
    Node<T> *root = nullptr;
};

template<class T>
void Bin_tree<T>::add(T val) {
    auto *node = new Node<T>;
    node->value = val;

    if (!root) {
        root = node;
        return;
    }

    Node<T> *point = root;
    while (true) {
        if (point->value <= node->value) {
            if (point->right == nullptr) {
                point->right = node;
                return;
            }

            point = point->right;
        } else {
            if (point->left == nullptr) {
                point->left = node;
                return;
            }

            point = point->left;
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    assert(n < 106);

    Bin_tree<int> int_bin_tree;
    int tmp = 0;

    for (size_t i = 0; i < n; i ++) {
        std::cin >> tmp;
        int_bin_tree.add(tmp);
    }

    return 0;
}