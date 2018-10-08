// Задача 1-3.
// Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
// n, m ≤ 100000. Указание.
// Обходите массив B от конца к началу.

// TEST
//  in:
//      4
//      -5 0 3 18
//      5
//      -10 -2 4 7 12
//      7
//  out:
//      3

#include <iostream>

int pair_count(int*, int, int*, int, int);

int main(int argc, const char** argv) {
    int n = 0;  // size of A
    std::cin >> n;
    int *A = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    int m = 0;  // size of B
    std::cin >> m;
    int *B = new int[m];
    for (size_t i = 0; i < m; i++) {
        std::cin >> B[i];
    }

//    for (size_t i = 0; i < n; i++) {
//        std::cout << A[i] << " ";
//    }
//    std::cout << std::endl;
//
//    for (size_t i = 0; i < m; i++) {
//        std::cout << B[i] << " ";
//    }
//    std::cout << std::endl;

    int k = 0;  // pair sum
    std::cin >> k;
    int res = pair_count(A, n, B, m, k);

    std::cout << res << std::endl;

    delete[] A;
    delete[] B;
    return 0;
}

int pair_count(int* A, int n, int* B, int m, int k) {
    int count = 0;
    return count;
}
