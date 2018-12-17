//
// Created by Pavel Pupchin on 2018-12-14.
//

#ifndef INC_1_MOD_GENERATOR_H
#define INC_1_MOD_GENERATOR_H

#include <random>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

class Generator {
public:
    Generator() = default;
    virtual ~Generator() = default;

    std::vector<std::pair<int, int>> generator(int sizeOfGraph);
};

#endif //INC_1_MOD_GENERATOR_H
