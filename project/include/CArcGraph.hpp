//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_CARCGRAPH_HPP
#define TP_1_SEM_CARCGRAPH_HPP

#include "IGraph.hpp"

#include <set>
#include <iostream>

class CArcGraph : public IGraph {
 public:
//    CArcGraph(size_t size) : vertices_mas(size * 2) {};
    CArcGraph(size_t size) {};
    ~CArcGraph() override = default;

    void add_edge(int from, int to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

    void print();
 private:
    std::vector<std::pair<int, int>> vertices_mas;
};

#endif //TP_1_SEM_CARCGRAPH_HPP
