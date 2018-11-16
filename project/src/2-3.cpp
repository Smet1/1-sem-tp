//
// Created by Kirill Smetankin on 15/11/2018.
//

#include <iostream>
#include <stack>
#include <vector>

template <class T>
struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
};

template <class T>
class Bin_tree {
 public:
    Bin_tree<T>() = default;
    ~Bin_tree();

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
    std::vector<Node<int> *> normal_order;
    std::vector<int> vector_print;

    Node<int> *buf;
    normal_order.push_back(in.root);

    while (!normal_order.empty()) {
        buf = normal_order.back();
        normal_order.pop_back();

        vector_print.push_back(buf->value);
        if (buf->left != nullptr) {
            normal_order.push_back(buf->left);
        }
        if (buf->right != nullptr) {
            normal_order.push_back(buf->right);
        }
    }

    for (auto i = vector_print.rbegin(); i != vector_print.rend(); i++) {
        os << *i << " ";
    }

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

template<class T>
Bin_tree<T>::~Bin_tree() {
    std::vector<Node<int> *> normal_order;
    std::cout << "=======\n~\n=======\n";
    Node<int> *buf;
    normal_order.push_back(root);

    while (!normal_order.empty()) {
        buf = normal_order.back();
        normal_order.pop_back();

        if (buf->left != nullptr) {
            normal_order.push_back(buf->left);
        }
        if (buf->right != nullptr) {
            normal_order.push_back(buf->right);
        }
        std::cout << buf->value << std::endl;
        delete(buf);
    }
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
    std::cout << std::endl;
    std::cout << int_bin_tree;

    return 0;
}