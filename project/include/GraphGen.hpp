//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_GRAPHGEN_HPP
#define TP_1_SEM_GRAPHGEN_HPP

#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

class GraphGen {
 public:
    GraphGen() = default;
    ~GraphGen() = default;

    std::vector<std::pair<int, int>> generate(size_t size);
};

#endif //TP_1_SEM_GRAPHGEN_HPP
