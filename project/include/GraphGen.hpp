//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_GRAPHGEN_HPP
#define TP_1_SEM_GRAPHGEN_HPP

#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <chrono>


class GraphGen {
 public:
    GraphGen() = default;
    ~GraphGen() = default;

    std::vector<std::pair<int, int>> generate(size_t size);
};

class Timer {
 public:
    void set_begin();
    void set_end();
    void calculate();
    void check_rps(int count);

 private:
    std::chrono::time_point<std::chrono::steady_clock> time_begin;
    std::chrono::time_point<std::chrono::steady_clock> time_end;
};

#endif //TP_1_SEM_GRAPHGEN_HPP
