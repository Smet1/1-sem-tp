//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <GraphGen.hpp>

template<class T>
T rand_num(const T &from = 0, const T &to = 10) {  // рандомное число в интервале
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<T> distr(from, to);

    return distr(generator);
}

std::vector<std::pair<int, int>> GraphGen::generate(size_t size) {
    std::vector<std::pair<int, int>> pair_mas;
    std::unordered_set<int> unique_vals;
    int edges = 0;
    int vert = 0;

    for (size_t i = 0; i < size; ++i) {
        edges = rand_num<int>(0, size);

        for (size_t j = 0; j < edges; ++j) {
            vert = rand_num<int>(0, size - 1);

            if (unique_vals.find(vert) == unique_vals.end()) {
                unique_vals.insert(vert);
                pair_mas.emplace_back(i, vert);
            }
        }
        unique_vals.clear();
    }

    return pair_mas;
}
void Timer::set_begin() {
    time_begin = std::chrono::steady_clock::now();
}
void Timer::set_end() {
    time_end = std::chrono::steady_clock::now();
}
void Timer::calculate(const std::string &str) {
    auto elapsed_mks = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_begin);
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin);
    std::cout << "\t\033[0;31m" << str << " time: " << elapsed_ms.count() << "ms, (" << elapsed_mks.count() << " µs)" << "\033[0m\n";
}
