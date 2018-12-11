//
// Created by Kirill Smetankin on 11/12/2018.
//

#ifndef TP_1_SEM_CMATRIXGRAPH_HPP
#define TP_1_SEM_CMATRIXGRAPH_HPP

#include "IGraph.hpp"

#include <iostream>

class CMatrixGraph : public IGraph {
 public:
    CMatrixGraph(size_t size);
    CMatrixGraph(const IGraph *graph);
    ~CMatrixGraph() override = default;

    void add_edge(int from, int to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;

    void print();

 private:
    std::vector<std::vector<bool>> matrix;  // матрица смежности
    size_t vertices_size;

};
#endif //TP_1_SEM_CMATRIXGRAPH_HPP
