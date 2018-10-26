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
#include <vector>


class Customer {
 public:
  Customer() : time_in(0), time_out(0), adv_view(0) {}
  Customer(int in, int out) : time_in(in), time_out(out), adv_view(0) {}
  ~Customer() = default;

  int get_time_in();
  int get_time_out();

  int set_time_out(int& val);
  int set_time_in(int& val);

  int inc_adv();
  int get_adv();

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

int Customer::inc_adv() {
  adv_view++;
  return adv_view;
}

int Customer::get_adv() {
  return adv_view;
}

std::ostream &operator<<(std::ostream &os, const Customer &in) {
//  os << "time_in = " << in.time_in << "time_out = " << in.time_out << std::endl;
  os << in.time_in << " " << in.time_out << ",";
  return os;
}

bool operator<(Customer const &a, Customer const &b) {
//  return (a.time_out < b.time_out || (a.time_out == b.time_out && a.time_in > b.time_in));
  if (a.time_out < b.time_out) {
    return true;
  }
  if (a.time_out == b.time_out) {
    return a.time_in > b.time_in;
  }
  return false;
}

bool operator>(Customer const &a, Customer const &b) {
//  return (a.time_out > b.time_out || (a.time_out == b.time_out && a.time_in < b.time_in));
  if (a.time_out > b.time_out) {
    return true;
  }
  if (a.time_out == b.time_out) {
    return a.time_in < b.time_in;
  }
  return false;
}

bool operator<=(Customer const &a, Customer const &b) {
//  return (a.time_out <= b.time_out || (a.time_out == b.time_out && a.time_in <= b.time_in));
  if (a.time_out <= b.time_out) {
    return true;
  }
  if (a.time_out == b.time_out) {
    return a.time_in <= b.time_in;
  }
  return false;
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
void print_vec(std::vector<T> &vec_in) {
  for (auto x : vec_in) {
    std::cout << x << " ";
  }
  std::cout << std::endl << "========"<< std::endl;
}

template <class T>
void merge_sort(std::vector<T> &in, size_t beg, size_t end) {
  if (end - beg < 2) {
    return;
  }
  if (end - beg == 2) {
    if (in[beg] > in[beg+1]) {
      std::swap(in[beg], in[beg+1]);
    }
    return;
  }

  merge_sort(in, beg, beg + (end - beg) / 2);
  merge_sort(in, beg + (end - beg) / 2, end);

  std::vector<T> tmp;
  size_t b1 = beg;
  size_t e1 = beg + (end - beg) / 2;
  size_t b2 = e1;

  while (tmp.size() < end - beg) {
    if (b1 >= e1 || (b2 < end && in[b2] < in[b1])) {
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
//  print_vec(tmp);
}

int count_adv(std::vector<Customer> in_vec) {
  int adv = 0;
  int adv_l = -1, adv_r = -1;  // время последних двух реклам

  int beg = 0;
  int j = beg;
  while (j < in_vec.size()) {
    for (;in_vec[j + 1].get_time_out() == in_vec[beg].get_time_out(); ++j) {}

    if (adv_r == in_vec[j].get_time_in()) {
      adv += 1;
      adv_l = adv_r;
      adv_r = in_vec[j].get_time_out();

    } else if (adv_l >= in_vec[j].get_time_in() && adv_l < in_vec[j].get_time_out()) {
      adv += 0;

    } else if (adv_r < in_vec[j].get_time_out() && adv_r > in_vec[j].get_time_in()) {
      adv += 1;
      adv_l = adv_r;
      adv_r = in_vec[j].get_time_out();

    } else {
      adv += 2;
      adv_r = in_vec[j].get_time_out();
      adv_l = adv_r - 1;

    }

    ++j;

//    std::cout << "adv_l = " << adv_l << ", adv_r = " << adv_r << std::endl;

  }
  return adv;

}

int main() {
  int n = 0;  // size of customers
  std::cin >> n;
  // checking n is valid
  int tmp, tmp1;

  std::vector<Customer> cus_vec;
  for (int i = 0; i < n; i++) {
    std::cin >> tmp >> tmp1;
//    assert(tmp > 0);
    assert(tmp < tmp1);
    cus_vec.emplace_back(tmp, tmp1);
  }

  merge_sort(cus_vec, 0, cus_vec.size());

  print_vec(cus_vec);

  auto res = count_adv(cus_vec);
  std::cout << res;
  return 0;
}
