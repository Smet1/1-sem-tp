#include <iostream>

template <class T>
struct Avl_node {
    T key;
    size_t height;
    Avl_node<T> *left;
    Avl_node<T> *right;

    explicit Avl_node<T>(T key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

template <class T>
class Avl_tree {
 public:
    Avl_tree() : root(nullptr) { }
    void add(T val);
 private:
    Avl_node<T> *root;
};

template<class T>
void Avl_tree<T>::add(T val) {
    auto *node = new Avl_node<T>(val);

    if (!root) {
        root = node;
        return;
    }

    Avl_node<T> *point = root;
    while (true) {
        if (point->key <= node->key) {
            if (point->right == nullptr) {
                point->right = node;

                break;
            }

            point = point->right;
        } else {
            if (point->left == nullptr) {
                point->left = node;

                break;
            }

            point = point->left;
        }
//        balance();
    }

//    std::cout << "balance\n";
    return;
}

////////////////////////////////////

int main() {
    int val = 0, stat = 0;
    int n = 0;

    std::cin >> n;

    Avl_tree<int> avl_tree;

    for (int i = 0; i < n; i++) {
        std::cin >> val >> stat;
        if (val < 0) {
            // remove
            std::cout << "remove\n";
        } else {
            // add
            avl_tree.add(val);
//            std::cout << "add\n";
        }
        // find stat
        std::cout << "stat\n\n";
    }

    return 0;
}