// Задача 1-1

#include <iostream>
#include <cassert>
#include <vector>

#define BASIC_CAPACITY 8

#define DEFAULT_CAPACITY 16

template<class T>
class Dynamic_mas {
 public:
    Dynamic_mas() : capacity(0), size(0) {
        array = nullptr;
    }

    explicit Dynamic_mas(size_t cap) : capacity(cap), size(0) {
        array = new T[cap];
    }

    ~Dynamic_mas() {
        delete[] array;
        capacity = 0;
        size = 0;
    }

    T& operator[](size_t index);

    void push_back(T val);  // запихуевание в конец
    T pop_back();

    void swap(size_t a, size_t b);

    T back();
    void insert(T val, size_t position);

    size_t get_capacity() const;
    size_t get_size() const;

    void print();

 private:
    T *array;
    size_t capacity;
    size_t size;

    void inc_capacity();  // увеличение капасити
};

template<class T>
void Dynamic_mas<T>::push_back(T val) {
    if (size == capacity) {
        inc_capacity();
    }

    array[size++] = val;
}

template<class T>
void Dynamic_mas<T>::inc_capacity() {
    size_t new_cap = (capacity * 2 < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capacity * 2;

    T *new_arr = new T[new_cap];
    size_t i = 0;
    for (; i < capacity; i++) {
        new_arr[i] = array[i];
    }

    delete[] array;

    array = new_arr;
    capacity = new_cap;
}

template<class T>
void Dynamic_mas<T>::print() {
    if (size == 0) {
        std::cout << "nothing to print, size = 0\n";
        return;
    } else {
        for (size_t i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
}

template<class T>
void Dynamic_mas<T>::swap(size_t a, size_t b) {
    std::swap(array[a], array[b]);
}

template<class T>
T Dynamic_mas<T>::pop_back() {
    T tmp = array[size--];
    return tmp;
}
template<class T>
T& Dynamic_mas<T>::operator[](size_t index) {
    assert(index <= capacity);
    return array[index];
}

template<class T>
size_t Dynamic_mas<T>::get_capacity() const {
    return capacity;
}

template<class T>
size_t Dynamic_mas<T>::get_size() const { return size; }

template<class T>
T Dynamic_mas<T>::back() {
    assert(size > 0);
    return array[size - 1];
}

template<class T>
void Dynamic_mas<T>::insert(T val, size_t position) {
//    assert(position <= capacity);

    array[position] = val;
    ++size;

    if (size >= 0.75 * capacity) {
        inc_capacity();
    }

}


/////////////////////////////////////////////

size_t hash_key(std::string &str, size_t hash_size) {
    size_t key = 0;
    int a = 3;
    for (char i : str) {
        key = (key * a + i) % hash_size;
    }

    return key;
}

class HashTable {
 public:
    HashTable();
    bool add(std::string val);
    bool find(std::string val);
    bool remove(std::string val);
    void print();
    size_t size() { return str_mas.get_size(); }
 private:
    Dynamic_mas<std::string> str_mas;
};

HashTable::HashTable() : str_mas(BASIC_CAPACITY) { }

bool HashTable::add(std::string val) {
    size_t key = hash_key(val, str_mas.get_capacity());
//    str_mas[key] = val;
    if (!find(val)) {
        str_mas.insert(val, key);
        return true;
    } else {
        return false;
    }

}

bool HashTable::find(std::string val) {
    size_t key = hash_key(val, str_mas.get_capacity());
    if (str_mas[key] == val) {
        return true;
    }

    return false;
}

bool HashTable::remove(std::string val) {
    size_t key = hash_key(val, str_mas.get_capacity());
    if (str_mas[key] == val) {
        str_mas[key].clear();
        return true;
    }
    return false;
}

void HashTable::print() {
    for (size_t i = 0; i < str_mas.get_capacity(); i++) {
        std::cout << "[" << i << "] |" << str_mas[i] << "|" << std::endl;
    }
}

void hash_interface(HashTable& ht, std::string& val, char& op) {
    switch (op) {
        case '+':
            if (ht.add(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        case '?':
            if (ht.find(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        case '-':
            if (ht.remove(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        default:
            std::cout << "net";
            return;
    }
}

int main() {
    char operation;
    std::string value;

    HashTable ht;

    for (size_t i = 0; i < 8; i++) {
        std::cin >> operation >> value;
        hash_interface(ht, value, operation);

        ht.print();
        std::cout << ht.size() << std::endl;
    }


    //    Dynamic_mas<int> test;
//    test.push_back(1);
//    test[3] = 2;
//    test.print();
    return 0;
}
