// Задача 3-2

// Реализовать дек с динамическим зацикленным буфером.
//
// Обрабатывать команды push * и pop *.
//
// Формат ввода
// В первой строке количество команд n. n ≤ 1000000.
//
// Каждая команда задаётся как 2 целых числа: a b.
//
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back

// Если дана команда pop *, то число b - ожидаемое значение.
// Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.


#include <iostream>
#include <cstring>
#include <cassert>


// TODO(): правило пяти



class Deq {  // deque
public:
  explicit Deq(size_t capacity) : capacity((int)capacity), head(0), tail(0) {
        array = new int[capacity];

        for (size_t i = 0; i < capacity; i++) {
            array[i] = 0;
        }
    }

    ~Deq();

    void push_front(int val);

    int pop_front();

    void push_back(int val);

    int pop_back();

    void print();

    Deq& operator=(const Deq& rvl) = delete;

private:
    int* array;
    int capacity;
    int head;
    int tail;

    int inc_capacity();;
};

Deq::~Deq() {
  delete [] (array);
  capacity = 0;
  head = 0;
  tail = 0;
}

void Deq::push_front(int val) {
  if (head == 0) {
    head = capacity - 1;
  } else {
    head--;
  }

  array[head] = val;
  if (head == tail) {
    inc_capacity();
  }
}

int Deq::pop_front() {
  if (head == tail) {
    return -1;
  } else {
    int res = array[head];
    array[head] = 0;
    head = (head + 1) % capacity;
    return res;
  }
}

void Deq::push_back(int val) {
  array[tail] = val;
  tail = (tail + 1) % capacity;  // тк зацикленный
  if (tail == head) {
    inc_capacity();
  }
}

int Deq::pop_back() {
  if (tail == head) {
    return -1;
  } else {
    if (tail == 0) {
      tail = capacity - 1;
    } else {
      tail--;
    }
    int res = array[tail];
    array[tail] = 0;
    return res;
  }

}

int Deq::inc_capacity() {
  int* new_arr = new int [capacity * 2];

  for (int i = 0; i < capacity; i++) {
    new_arr[i] = array[(head + i) % capacity];

  }
  delete[](array);

  array = new_arr;
  head = 0;
  tail = capacity;
  capacity *= 2;

  return 0;
}

void Deq::print() {
  for (size_t i = 0; i < capacity; i++) {
    std::cout << array[i] << " ";
  }

  std::cout << std::endl;
}

bool do_command(Deq& deq, int com, int val) {
  switch (com) {
    case 1:
      deq.push_front(val);
      return true;

    case 3:
      deq.push_back(val);
      return true;

    case 2:
      return val == deq.pop_front();

    case 4:
      return val == deq.pop_back();

    default:
      return false;
  }
}

int main() {
    int n = 0;  // size of A
    std::cin >> n;
    // checking n is valid
    assert(n <= 1000000);

    Deq deq(5);
    bool res = true;
    int com = 0, val = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> com >> val;
        if (res) {
            res = do_command(deq, com, val);
//            deq.print();
        }
    }

    if (res) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }



    return 0;
}
