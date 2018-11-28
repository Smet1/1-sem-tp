#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
    size_t level = 0;
};

template <class T>
class Bin_tree {
 public:
    Bin_tree<T>() = default;
    ~Bin_tree();

    void add(T val);
    void print_post();
    size_t get_max_width();
 private:
    Node<T> *root = nullptr;
    std::vector<size_t> count_levels;
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
        node->level++;
        if (point->value <= node->value) {
            if (point->right == nullptr) {
                point->right = node;

                if (node->level > count_levels.size()) {
                    count_levels.push_back(1);
                } else {
                    count_levels[node->level]++;
                }
                return;
            }

            point = point->right;
        } else {
            if (point->left == nullptr) {
                point->left = node;

                if (node->level > count_levels.size()) {
                    count_levels.push_back(1);
                } else {
                    count_levels[node->level]++;
                }
                return;
            }

            point = point->left;
        }
    }
}

template <class T>
void Bin_tree<T>::print_post() {
    std::vector<Node<int> *> normal_order;
    std::vector<int> vector_print;

    Node<int> *buf;
    normal_order.push_back(root);

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
        std::cout << *i << " ";
    }
}

template<class T>
Bin_tree<T>::~Bin_tree() {
    std::vector<Node<int> *> normal_order;
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

        delete(buf);
    }
}

template<class T>
size_t Bin_tree<T>::get_max_width() {
    size_t res = 0;
    for (auto i : count_levels) {
        res = std::max(res, i);
    }

    return res;
}

int main() {
    int n = 0;
    std::cin >> n;

    Bin_tree<int> int_bin_tree;
    int key = 0, priority = 0;

    for (size_t i = 0; i < n; i ++) {
        std::cin >> key >> priority;

        int_bin_tree.add(key);
    }

    int_bin_tree.print_post();

    size_t max = int_bin_tree.get_max_width();
    std::cout << std::endl << max;
    return 0;
}