// задача 6-4

// Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
// Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число,
// которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
// Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.

// Описание для случая прохода от начала массива к концу:
// - Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
// - Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
//   Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
//   Последним элементом лежит опорный.
// - Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
// - Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
// - Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
//   Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
// - В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
//

// вызывается функция сортировки на массиве, левая граница и правая сортировки
// возвращает структуру, там найден элемент или нет
// вайл в структуре не тру


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

  int *new_arr = new int[new_cap];
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
T rand_num(const T &from = 0, const T &to = 10) {  // рандомное число в интервале
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<T> distr(from, to);

  return distr(generator);
}

template<class T>
T partition(Dynamic_mas<T> &arr, int begin, int end) {
  int rand = rand_num(begin, end - 1);

  arr.swap((size_t) rand, (size_t) end - 1);

  int i = end - 2;
  int j = end - 2;

  while (j >= 0){
    if (arr[j] > arr[end - 1]){
      arr.swap(i, j);
      i--;
      j--;
    } else {
      j--;
    }
  }
  arr.swap(++i, end - 1);

  return i;
}

template<class T>
T k_statistic(Dynamic_mas<T> &arr, int begin, int end, int k) {
  assert(begin < end);

  int pivot = partition(arr, begin, end);
  while (pivot != k) {
    if (pivot > k) {
      end = pivot;
      pivot = partition(arr, begin, end);
    } else if (pivot < k) {
      begin = pivot;
      pivot = partition(arr, begin, end);
    }
  }

  return arr[pivot];
}

int main() {
  int n = 0;
  std::cin >> n;
  // checking n is valid
  assert(n < 1000000000);
  assert(n >= 0);

  int k = 0;
  std::cin >> k;
//  assert(k < (n - 1));
//  assert(k >= 0);

  Dynamic_mas<int> int_mas(n);

  int tmp = 0;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> tmp;
    int_mas.push_back(tmp);
  }

  std::cout << k_statistic(int_mas, 0, n, k) << std::endl;

  return 0;
}
