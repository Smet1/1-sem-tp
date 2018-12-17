//
// Created by Pavel Pupchin on 2018-12-14.
//

#include "Generator.h"

std::vector<std::pair<int, int>> Generator::generator(int sizeOfGraph) {
    std::vector<std::pair<int, int>> vectorPairs;
    std::unordered_set<int> unique;
//    int randomNum = std::rand() % sizeOfGraph;

    for (size_t i = 0; i < sizeOfGraph; ++i) {
        int tempEdge = rand() % sizeOfGraph + 1;
        for (size_t j = 0; j < tempEdge; ++j) {
            int tempVertice = rand() % (sizeOfGraph - 1) + 1;
            if (unique.find(tempVertice) == unique.end()) {
                unique.insert(tempVertice);
                vectorPairs.emplace_back(i, tempVertice);
            }
        }
        unique.clear();
    }
    return vectorPairs;
};