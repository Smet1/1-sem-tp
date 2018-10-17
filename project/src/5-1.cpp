// задача 5-1

// В супермаркете решили оптимизировать показ рекламы.
// Известно расписание прихода и ухода покупателей (два целых числа).
// Каждому покупателю необходимо показать минимум 2 рекламы.
// Рекламу можно транслировать только в целочисленные моменты времени.
// Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
// В каждый момент времени может показываться только одна реклама.
// Считается, что реклама показывается мгновенно.
// Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.

// Требуется определить минимальное число показов рекламы.


#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>

#define DEFAULT_CAPACITY 10

class Cus_vec {
public:
    Cus_vec() : capacity(0), size(0) {
        array = nullptr;
    }

    explicit Cus_vec(size_t cap) : capacity(cap), size(0) {
        array = new int[cap];
    }

    ~Cus_vec() {
        delete[] array;
        capacity = 0;
        size = 0;
    }

    int get_elem(size_t index) const;  // получение элемента по индексу

    int operator[](size_t index) const;

    void push_back(int val);  // запихуевание в конец
    int pop_back();
    void print();
    size_t get_size() const { return size; }
    void swap(size_t a, size_t b);
    int back() {
        assert(size > 0);
        return array[size - 1];
    }


private:
    int* array;
    size_t capacity;
    size_t size;

    void inc_capacity();  // увеличение капасити
};

int Cus_vec::operator[](size_t index) const {
    return get_elem(index);
}

int Cus_vec::get_elem(size_t index) const {
    assert(index <= size);  // мб не ассерт, но вот так
    return array[index];
}

void Cus_vec::push_back(int val) {
    if (size == capacity) {
        inc_capacity();
    }

    array[size++] = val;
}

void Cus_vec::inc_capacity() {
    size_t new_cap = (capacity * 2 < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capacity * 2;

    int* new_arr = new int[new_cap];
    size_t i = 0;
    for (; i < size; i++) {
        new_arr[i] = array[i];
    }

    delete[] array;

    array = new_arr;
    capacity = new_cap;
}

void Cus_vec::print() {
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

void Cus_vec::swap(size_t a, size_t b) {
    std::swap(array[a], array[b]);
}

int Cus_vec::pop_back() {
    int tmp = array[size--];
    return tmp;
}

/////////////////////////////////////////////////////////////////////


int main() {
    int n = 0;  // size of A
    std::cin >> n;
    // checking n is valid

    Heap my_heap((size_t)n);
    int time_in = 0, time_out = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> time_in >> time_out;
        assert(0 <= time_in);
        assert(time_in <= 1000000000);

        assert(0 <= time_out);
        assert(time_out <= 1000000000);

        my_heap.drop_bigger_vals(time_in);
        my_heap.add(time_out);
//        my_heap.arr_print();
    }

    std::cout << my_heap.get_size();

    return 0;
}
