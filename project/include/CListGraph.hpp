//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_CLISTGRAPH_HPP
#define TP_1_SEM_CLISTGRAPH_HPP

#include <ostream>

#include "IGraph.hpp"

class CListGraph : public IGraph {
 public:
    explicit CListGraph(size_t vertices_count);
    CListGraph(const IGraph *graph);
    ~CListGraph() override = default;

    void add_edge(int from, int to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

    void print(std::ostream &out);

 private:
    std::vector<std::vector<int>> out_edges_;
    std::vector<std::vector<int>> in_edges_;
};

#endif //TP_1_SEM_CLISTGRAPH_HPP
