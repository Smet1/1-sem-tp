// Задача 1-3.
// Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
// n, m ≤ 100000. Указание.
// Обходите массив B от конца к началу.
#include <iostream>

int pair_count();

int main(int argc, const char** argv) {
    int n = 0, m = 0, k = 0;
    std::cin >> n;
    int *A = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> A[n];
    }
    for (size_t i = 0; i < n; i++) {
        std::cout << A[n] << " ";
    }
    std::cout << std::endl;

//    int res = pair_count();

    delete[] (A);
    return 0;
}
