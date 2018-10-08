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

    return 0;
}
