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

// сортировать по концу интервалов
// по концам по возрастанию
// начало по убыванию

// если не видел, то показывать в 2 самых послдених момента
// запоминать время двух последних реклам


#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>

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

class Customer {
 public:
  Customer() : time_in(0), time_out(0), adv_view(0) {}
  Customer(int in, int out) : time_in(in), time_out(out), adv_view(0) {}
  ~Customer() = default;

  int get_time_in();
  int get_time_out();

  int set_time_out(int& val);
  int set_time_in(int& val);

  friend bool operator<(Customer const &a, Customer const &b);
  friend bool operator>(Customer const &a, Customer const &b);
  friend bool operator<=(Customer const &a, Customer const &b);
  friend std::ostream& operator<<(std::ostream& os, const Customer& in);
  Customer&operator=(const Customer& right);

 private:
  int time_in;
  int time_out;
  int adv_view;  // сколько рекламы видел
};

int Customer::get_time_in() {
  return time_in;
}

int Customer::get_time_out() {
  return time_out;
}

int Customer::set_time_out(int &val) {
  time_out = val;
  return time_out;
}

int Customer::set_time_in(int &val) {
  time_in = val;
  return time_in;
}

std::ostream &operator<<(std::ostream &os, const Customer &in) {
//  os << "time_in = " << in.time_in << "time_out = " << in.time_out << std::endl;
  os << in.time_in << " " << in.time_out << std::endl;
  return os;
}

bool operator<(Customer const &a, Customer const &b) {
  return (a.time_out < b.time_out || (a.time_out == b.time_out && a.time_in > b.time_in));
}

bool operator>(Customer const &a, Customer const &b) {
  return (a.time_out > b.time_out || (a.time_out == b.time_out && a.time_in < b.time_in));
}

bool operator<=(Customer const &a, Customer const &b) {
  return (a.time_out <= b.time_out || (a.time_out == b.time_out && a.time_in <= b.time_in));
}

Customer &Customer::operator=(const Customer &right) {
  if (this == &right) {
    return *this;
  }

  time_out = right.time_out;
  time_in = right.time_in;

  return *this;
}

/////////////////////////////////////////////////////////////

template <class T>
void merge_sort(Dynamic_mas<T> &in, size_t beg, size_t end) {
  if (end - beg < 2) {
    return;
  }
  if (end - beg == 2) {
    if (in[beg+1] < in[beg]) {
      in.swap(beg, beg + 1);
    }
    return;
  }

  merge_sort(in, beg, beg + (end - beg) / 2);
  merge_sort(in, beg + (end - beg) / 2, end);

  Dynamic_mas<T> tmp;
  size_t b1 = beg;
  size_t e1 = beg + (end - beg) / 2;
  size_t b2 = e1;

  while (tmp.get_size() < end - beg) {
    if (b1 >= e1 || (b2 < end && in[b2] <= in[b1])) {
      tmp.push_back(in[b2]);
      ++b2;
    } else {
      tmp.push_back(in[b1]);
      ++b1;
    }
  }

  for (size_t i = beg; i < end; i++) {
    in[i] = tmp[i - beg];
  }

//  tmp.print();
}

int main() {
  int n = 0;  // size of customers
  std::cin >> n;
  // checking n is valid
//    int tmp, tmp1;
//    std::cin >> tmp >> tmp1;
//    Customer a(tmp, tmp1);
//
//    std::cin >> tmp >> tmp1;
//    Customer b(tmp, tmp1);
//
//    if (a < b) {
//      std::cout << "a < b";
//    } else {
//      std::cout << "a > b";
//    }

  Dynamic_mas<Customer> cus_mas(n);
  int tmp, tmp1;

  for (int i = 0; i < n; i++) {
    std::cin >> tmp >> tmp1;

    cus_mas.push_back(Customer(tmp, tmp1));
  }
  cus_mas.print();
  merge_sort(cus_mas, 0, n);


  return 0;
}
