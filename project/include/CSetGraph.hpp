//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_CSETGRAPH_HPP
#define TP_1_SEM_CSETGRAPH_HPP

#include <IGraph.hpp>

#include <iostream>
#include <unordered_set>

class CSetGraph : public IGraph {
 public:
    CSetGraph(size_t size) : vertices(size), vertices_size(size) {}
    CSetGraph(const IGraph *graph);
    ~CSetGraph() override = default;

    void add_edge(int from, int to) override;
    size_t vertices_count() const override;
    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

    void print();
 private:
    std::vector<std::unordered_set<int>> vertices;
    size_t vertices_size;

};

#endif //TP_1_SEM_CSETGRAPH_HPP
