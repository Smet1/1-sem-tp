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
    Bin_tree() = default;
    ~Bin_tree();

    void add(T val);
    void print_post();
    int get_max_width();
 private:
    void count_width();
    Node<T> *root = nullptr;
    std::vector<int> count_levels;
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

//                if (node->level > count_levels.size()) {
//                    count_levels.push_back(1);
//                } else {
//                    count_levels[node->level]++;
//                }
                return;
            }

            point = point->right;
        } else {
            if (point->left == nullptr) {
                point->left = node;

//                if (node->level > count_levels.size()) {
//                    count_levels.push_back(1);
//                } else {
//                    count_levels[node->level]++;
//                }
                return;
            }

            point = point->left;
        }
    }
}

template <class T>
void Bin_tree<T>::print_post() {
    std::vector<Node<T> *> normal_order;
    std::vector<T> vector_print;

    Node<T> *buf;
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
    std::vector<Node<T> *> normal_order;
    Node<T> *buf;
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
int Bin_tree<T>::get_max_width() {
    int res = 0;
    count_width();
    for (auto i : count_levels) {
        res = std::max(res, i);
    }

    return res;
}

template<class T>
void Bin_tree<T>::count_width() {
    std::vector<Node<T> *> tmp;  // первый уровень
    std::vector<Node<T> *> tmp_next;  // следуюший за ним

    if (root) {
        tmp.push_back(root);
        count_levels.push_back(1);
    } else {
        count_levels.push_back(0);
        return;
    }

    while (true) {
        for (auto &i : tmp) {
            if (i->left != nullptr) {
                tmp_next.push_back(i->left);
            }
            if (i->right != nullptr) {
                tmp_next.push_back(i->right);
            }
        }
        if (tmp_next.empty()) {
            return;
        }
        count_levels.push_back(static_cast<int &&>(tmp_next.size()));
        tmp = tmp_next;
        tmp_next.clear();
    }
}

/////////////////////////////////////////////////////////
template <class T>
struct Treap_node {
    T val;
    T priority;
    Treap_node *left;
    Treap_node *right;
    size_t level;

    Treap_node(T val, T priority) : val(val), priority(priority), left(nullptr), right(nullptr), level(0) { }
};

template <class T>
class Treap {
 public:
    Treap() = default;
    ~Treap();
    void add(T val, T priority);
    void split(Treap_node<T> *current_node, T &val, Treap_node<T> *&left, Treap_node<T> *&right);
    int get_max_width();

 private:
    void count_width();
    Treap_node<T> *root = nullptr;
    std::vector<int> count_levels;
};

template<class T>
void Treap<T>::add(T val, T priority) {
    auto *node = new Treap_node<T>(val, priority);

    Treap_node<T> *point = root;
    Treap_node<T> *prev_point = root;
    size_t levelOfNode = 0;

    if (point == nullptr) {
        root = node;
        return;
    }

    while (point != nullptr && priority <= point->priority) {
        prev_point = point;
        if (val <= point->val) {
            point = point->left;
            levelOfNode++;
        }
        else {
            point = point->right;
            levelOfNode++;
        }
    }

    split(point, val, node->left, node->right);

    if (point == root) {
        prev_point->level = levelOfNode;
        root = node;
    } else if (val <= prev_point->val) {
        prev_point->level = levelOfNode;
        prev_point->left = node;
    } else {
        prev_point->level = levelOfNode;
        prev_point->right = node;
    }
}
template<class T>
void Treap<T>::split(Treap_node<T> *current_node,
                     T &val,
                     Treap_node<T> *&left,
                     Treap_node<T> *&right) {

    if (current_node == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (current_node->val <= val) {
        split (current_node->right, val, current_node->right, right);
        left = current_node;
    } else {
        split (current_node->left, val, left, current_node->left);
        right = current_node;
    }
}

template<class T>
void Treap<T>::count_width() {
    std::vector<Treap_node<T> *> tmp;  // первый уровень
    std::vector<Treap_node<T> *> tmp_next;  // следуюший за ним

    if (root) {
        tmp.push_back(root);
        count_levels.push_back(1);
    } else {
        count_levels.push_back(0);
        return;
    }

    while (true) {
        for (auto &i : tmp) {
            if (i->left != nullptr) {
                tmp_next.push_back(i->left);
            }
            if (i->right != nullptr) {
                tmp_next.push_back(i->right);
            }
        }
        if (tmp_next.empty()) {
            return;
        }
        count_levels.push_back(static_cast<int &&>(tmp_next.size()));
        tmp = tmp_next;
        tmp_next.clear();
    }
}

template<class T>
int Treap<T>::get_max_width() {
    count_width();

    int res = 0;
    for (auto &i : count_levels) {
        res = std::max(res, i);
    }

    return res;
}

template<class T>
Treap<T>::~Treap() {
    std::vector<Treap_node<T> *> normal_order;
    Treap_node<T> *buf;
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

int main() {
    int n = 0;
    std::cin >> n;

    Bin_tree<int> int_bin_tree;
    Treap<int> int_treap;

    int key = 0, priority = 0;

    for (size_t i = 0; i < n; i ++) {
        std::cin >> key >> priority;

        int_bin_tree.add(key);
        int_treap.add(key, priority);
    }
//    std::cout << int_treap.get_max_width() << std::endl << int_bin_tree.get_max_width() << std::endl;

    std::cout << int_treap.get_max_width() - int_bin_tree.get_max_width();

    return 0;
}