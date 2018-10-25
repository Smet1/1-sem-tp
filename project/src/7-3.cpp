// задача 7-3

// Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 1000000.
// Отсортировать массив методом MSD по битам (бинарный QuickSort).


#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>
#include <random>

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
  T *array;
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

/////////////////////////////////////////////////////////////////////
template <class T>
int get_bit(T num, int digit) {
  return (num >> digit) & 1;
}


template <class T>
void bin_QuickSort(Dynamic_mas<T>& in_mas, int left, int right, int digit) {
  if (right <= left || digit < 0) {
    return;
  }

  int i = left;
  int j = right;

  while (i != j) {
    while ((get_bit(in_mas[i], digit)) == 0 && (i < j)) {
      i++;
    }

    while ((get_bit(in_mas[j], digit)) == 1 && (j > i)) {
      j--;
    }

    in_mas.swap(i, j);
  }

  if (get_bit(in_mas[right], digit) == 0){
    j++;
  }

  bin_QuickSort(in_mas, left, j - 1, digit - 1);
  bin_QuickSort(in_mas, j, right, digit - 1);

}

int main() {
  int n = 0;
  std::cin >> n;
  // checking n is valid
  assert(n < 1000000);
  assert(n >= 0);

  Dynamic_mas<long long> ll_mas(n);

  long long tmp = 0;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> tmp;
    ll_mas.push_back(tmp);
  }

  bin_QuickSort(ll_mas, 0, n - 1, 63);
  ll_mas.print();

  return 0;
}
