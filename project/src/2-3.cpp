//
// Created by Kirill Smetankin on 15/11/2018.
//

#include <iostream>
#include <stack>

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
    friend std::ostream& operator<<(std::ostream &os, const Bin_tree<T> &in);
    void recursive_print(Node<T> *point);
    Node<T> *get_root();
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

std::ostream &operator<<(std::ostream &os, const Bin_tree<int> &in) {
    std::stack<Node<int> *> tmp;

    tmp.push(in.root);

    Node<int> *it = tmp.top();
    tmp.pop();
    os << "chlen\n";
    return os;
}

template<class T>
void Bin_tree<T>::recursive_print(Node<T> *point) {
    if (point == nullptr)
        return;
    recursive_print(point->left);
    recursive_print(point->right);

    std::cout << point->value << " ";
}

template<class T>
Node<T> *Bin_tree<T>::get_root() {
    return root;
}

int main() {
    int n = 0;
    std::cin >> n;
    assert(n < 106);

    Bin_tree<int> int_bin_tree;
    int input = 0;

    for (size_t i = 0; i < n; i ++) {
        std::cin >> input;

        assert(input >= -231);
        assert(input <= 231);

        int_bin_tree.add(input);
    }

    int_bin_tree.recursive_print(int_bin_tree.get_root());

//    std::cout << int_bin_tree;

    return 0;
}