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

#define DEFAULT_CAPACITY 16

// TODO(): перемеиновать вектор в массив
// TODO(): шаблон для вектора
// TODO(): дефолт размер 16 и добавить в конструктор дефолт размер
// TODO(): правило пяти
// TODO(): хранить хип наоборот

template <class T>
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

    T operator[](size_t index) const;

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
    T* array;
    size_t capacity;
    size_t size;

    void inc_capacity();  // увеличение капасити
};

template<class T>
T Dynamic_mas<T>::operator[](size_t index) const {
    return get_elem(index);
}

template<class T>
T Dynamic_mas<T>::get_elem(size_t index) const {
    assert(index <= size);  // мб не ассерт, но вот так
    return array[index];
}

template<class T>
void Dynamic_mas<T>::push_back(int val) {
    if (size == capacity) {
        inc_capacity();
    }

    array[size++] = val;
}

template<class T>
void Dynamic_mas<T>::inc_capacity() {
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
    int tmp = array[size--];
    return tmp;
}

/////////////////////////////////////////////////////////////////////

template<class T>
class Heap {
public:
    Heap() : array(DEFAULT_CAPACITY), max_size(0) {}
    explicit Heap(size_t cap) : array(cap), max_size(0) {}
    ~Heap() {
//        array.Dynamic_mas_mas();
        max_size = 0;
    }

    void arr_print();
    T pop_max();  // извлечение максимума
    void add(int val);
    void drop_bigger_vals(int val);

    size_t get_size() const { return max_size; }

private:
    Dynamic_mas<T> array;
    size_t max_size;

    void §_down(size_t i);  // просеивание вниз
    void sift_up(size_t i);  // просеивание вверх

};

template<class T>
void Heap<T>::arr_print() {
    array.print();
}

template<class T>
void Heap<T>::sift_down(size_t i) {
    size_t beg = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t max = i;

    if (beg < array.get_size() && array[beg] < array[i]) {
        max = beg;
    }
    if (right < array.get_size() && array[right] < array[max]) {
        max = right;
    }

    if (max != i) {
        array.swap(i, max);
        sift_down(max);
    }

}

template<class T>
void Heap<T>::sift_up(size_t i) {
    while (i > 0) {
        size_t par = (i - 1) / 2;
        if (array[i] >= array[par]) {
            return;
        }

        array.swap(i, par);
        i = par;
    }
}

template<class T>
T Heap<T>::pop_max() {
    int res = array[0];

    array.swap(0, array.get_size() - 1);
    array.pop_back();

    if (array.get_size() != 0) {
        sift_down(0);
    }
    return res;
}

template<class T>
void Heap<T>::add(T val) {
    array.push_back(val);
    sift_up(array.get_size() - 1);

    if (array.get_size() > max_size) {
        max_size++;
    }
}

template<class T>
void Heap<T>::drop_bigger_vals(int val) {
    while (val > array[0]) {
        if (array.get_size() == 0) {
            return;
        }
        pop_max();
    }

}

int main() {
    int n = 0;  // size of A
    std::cin >> n;
    // checking n is valid

    Heap<int> my_heap((size_t)n);
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
