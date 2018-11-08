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

    T get_elem(size_t index) const;  // получение элемента по индексу

    const T operator[](size_t index) const;
    T& operator[](size_t index);

    void push_back(T val);  // запихуевание в конец
    T pop_back();
    void print();
    size_t get_size() const { return size; }
    void swap(size_t a, size_t b);
    T back() {
        assert(size > 0);
        return array[size - 1];
    }

 private:
    T *array;
    size_t capacity;
    size_t size;

    void inc_capacity();  // увеличение капасити
};

template<class T>
const T Dynamic_mas<T>::operator[](size_t index) const {
    return get_elem(index);
}

template<class T>
T Dynamic_mas<T>::get_elem(size_t index) const {
    assert(index <= size);  // мб не ассерт, но вот так
    return array[index];
}

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
    for (; i < size; i++) {
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
        for (size_t i = 0; i < capacity; i++) {
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

/////////////////////////////////////////////

class HashTable {
 public:
    HashTable();
    bool add(std::string val);
    bool find(std::string val);
    bool remove(std::string val);

 private:
    Dynamic_mas<std::string> str_mas;
};

HashTable::HashTable() : str_mas(BASIC_CAPACITY) { }

bool HashTable::add(std::string val) {
    return false;
}

bool HashTable::find(std::string val) {
    return false;
}

bool HashTable::remove(std::string val) {
    return false;
}


int main() {
    char operation;
    std::string value;

    std::cin >> operation >> value;

    Dynamic_mas<int> test;
    test.push_back(1);
    test[3] = 2;
    test.print();
    return 0;
}
