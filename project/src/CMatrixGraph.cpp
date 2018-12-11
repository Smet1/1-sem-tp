//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CMatrixGraph.hpp>

CMatrixGraph::CMatrixGraph(size_t size) : matrix(size, std::vector<bool>(size, false)) {}

void CMatrixGraph::add_edge(int from, int to) {
    matrix[from][to] = true;
}
size_t CMatrixGraph::vertices_count() const {
    // TODO(): сделать как яков на семе, мой варик неправильный
//    size_t counter = 0;
//    for (auto i : matrix) {
//        for (auto j : i) {
//            if (j)
//                ++counter;
//        }
//    }
//    return counter;
    return matrix[0].size();
}
std::vector<int> CMatrixGraph::get_next_vertices(int vertex) const {
    std::vector<int> next_vertices;
    for (size_t vert = 0; vert < vertices_count(); ++vert) {
        if (matrix[vertex][vert]) {
            next_vertices.push_back(static_cast<int &&>(vert));
        }
    }

    return next_vertices;
}
std::vector<int> CMatrixGraph::get_prev_vertices(int vertex) const {
    std::vector<int> prev_vertices;
    for (size_t vert = 0; vert < vertices_count(); ++vert) {
        if (matrix[vert][vertex]) {
            prev_vertices.push_back(static_cast<int &&>(vert));
        }
    }

    return prev_vertices;
}
void CMatrixGraph::print() {
//    std::cout << " ";
//    for (size_t k = 0; k < vertices_count(); ++k) {
//        std::cout << k << " ";
//    }
//    std::cout << std::endl;

    size_t counter = 0;
    for (auto i : matrix) {
        std::cout << "[" << counter++ << "]: ";

        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
