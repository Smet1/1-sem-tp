// Задача 2-2

// Дан массив целых чисел А[0..n-1].
// Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
// Найти m за O( log m ).
// 2 ≤ n ≤ 10000.

// IN:
//      10
//      1 2 3 4 5 6 7 6 5 4
// OUT:
//      6
#include <iostream>
#include <cassert>

int search_pos(const int*, int);

int main() {
    int n = 0;  // size of A
    std::cin >> n;
    // checking n is valid
    assert(n <= 10000);
    assert(n >= 2);

    int *A = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    int res = search_pos(A, n);
//    std::cout << "A[" << res << "] = " << A[res];
    std::cout << res;
    delete[] A;
    return 0;
}

int search_pos(const int* A, int n) {
    int i = 1, beg = 0, end = n;

    while (i < n) {
        if (A[i - 1] > A[i]) {
            beg = i / 2;
            end = i;
            break;
        }
        i *= 2;  // 1 -> 2 -> 4 ...
    }

    int m = (end + beg) / 2;
    while (end - beg > 1) {
        m = (end + beg) / 2;
        if (A[m - 1] < A[m]) {
            beg = m;
        } else if (A[m - 1] > A[m]) {
            end = m;
        }
    }
    return beg;
}
