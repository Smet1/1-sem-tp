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

class Heap {
public:
    Heap() : array(DEFAULT_CAPACITY), max_size(0) {}
    explicit Heap(size_t cap) : array(cap), max_size(0) {}
    ~Heap() {
//        array.~Cus_vec();
        max_size = 0;
    }

    void arr_print();
    int pop_max();  // извлечение максимума
    void add(int val);
    void drop_bigger_vals(int val);

    size_t get_size() const { return max_size; }

private:
    Cus_vec array;
    size_t max_size;

    void sift_down(size_t i);  // просеивание вниз
    void sift_up(size_t i);  // просеивание вверх

};

void Heap::arr_print() {
    array.print();
}

void Heap::sift_down(size_t i) {
    size_t beg = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t max = i;

    if (beg < array.get_size() && array[beg] > array[i]) {
        max = beg;
    }
    if (right < array.get_size() && array[right] > array[max]) {
        max = right;
    }

    if (max != i) {
        array.swap(i, max);
        sift_down(max);
    }

}

void Heap::sift_up(size_t i) {
    while (i > 0) {
        size_t par = (i - 1) / 2;
        if (array[i] <= array[par]) {
            return;
        }

        array.swap(i, par);
        i = par;
    }
}

int Heap::pop_max() {
    int res = array[0];

    array.swap(0, array.get_size() - 1);
    array.pop_back();

    if (array.get_size() != 0) {
        sift_down(0);
    }
    return res;
}

void Heap::add(int val) {
    array.push_back(val);
    sift_up(array.get_size() - 1);

    if (array.get_size() > max_size) {
        max_size++;
    }
}

void Heap::drop_bigger_vals(int val) {
//    auto tmp = array[0];
//    while (val < array[0]) {
//        if (array.get_size() == 0) {
//            return;
//        }
//        pop_max();
//    }

    size_t i = 0;
    while (val < array[i] && i < array.get_size()) {
        if (array.get_size() == 0) {
            return;
        }

        array.swap(0, i);
        pop_max();

        std::cout << "--sz = " << array.get_size() << std::endl;

        i++;
    }
}

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
        my_heap.arr_print();
    }

    std::cout << my_heap.get_size();

    return 0;
}
