// Задача 4-3

// На вокзале есть некоторое количество тупиков, куда прибывают электрички.
// Этот вокзал является их конечной станцией.
// Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия,
// а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
// Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
// При этом если электричка из какого-то тупика отправилась в момент времени X,
// то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
// прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
// Напишите программу, которая по данному расписанию определяет,
// какое минимальное количество тупиков требуется для работы вокзала.
//
// Формат ввода
// Вначале вводится n - количество электричек в расписании.
// Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления.
// Время - натуральное число от 0 до 1 000 000 000. Строки в расписании упорядочены по времени прибытия.
//
// Формат вывода
// Натуральное число - минимальное количеством тупиков.



#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

#define DEFAULT_CAPACITY 10

class Cus_vec {
public:
    Cus_vec() : capacity(0), size(0) {
        array = nullptr;
    }

    Cus_vec(size_t cap) : capacity(cap), size(0) {
        array = new int [cap];

        // зануляю выделенную память, необязательная часть
//        for (size_t i = 0; i < capacity; i++) {
//            array[i] = 0;
//        }
    }

    ~Cus_vec() {
        delete[](array);
        capacity = 0;
        size = 0;
    }

    int get_elem(size_t index) const;  // получение элемента по индексу

    int operator[](size_t index) const;

    void push_back(int val);  // запихуевание в конец

    void print();

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

    // зануляю выделенную память, необязательная часть
//    for (; i < new_cap; i++) {
//        new_arr[i] = 0;
//    }

    delete[](array);

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

class Heap {
public:
    Heap(int size) : capacity(size), size(0), max_size(0) {
        array = new int[capacity];

        for (size_t i = 0; i < capacity; i++) {
            array[i] = 0;
        }
    }

    ~Heap() {
        delete [] (array);
        capacity = 0;
        size = 0;
        max_size = 0;
    }

private:
    int* array;
    int capacity;
    int size;
    int max_size;
};

int main() {
    int n = 0;  // size of A
    std::cin >> n;
    // checking n is valid
    assert(n >= 0);
    assert(n <= 1000000000);



    return 0;
}
