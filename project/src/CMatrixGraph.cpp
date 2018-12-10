//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CMatrixGraph.hpp>

CMatrixGraph::CMatrixGraph(size_t size) : matrix(size, std::vector<bool>(size, false)) {}

void CMatrixGraph::add_edge(int from, int to) {
    matrix[from][to] = true;
}
size_t CMatrixGraph::vertices_count() const {
    size_t counter = 0;
    for (auto i : matrix) {
        for (auto j : i) {
            if (j)
                ++counter;
        }
    }
    return counter;
}
std::vector<int> CMatrixGraph::get_next_vertices(int vertex) const {
    return std::vector<int>();
}
std::vector<int> CMatrixGraph::get_prev_vertices(int vertex) const {
    return std::vector<int>();
}
