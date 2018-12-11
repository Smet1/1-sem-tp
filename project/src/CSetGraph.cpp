//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CSetGraph.hpp>

void CSetGraph::add_edge(int from, int to) {
    vertices[from].insert(to);
}

size_t CSetGraph::vertices_count() const {
    return 0;
}

std::vector<int> CSetGraph::get_next_vertices(int vertex) const {
    return std::vector<int>(vertices[vertex].begin(), vertices[vertex].end());
}

std::vector<int> CSetGraph::get_prev_vertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].find(vertex) != vertices[i].end()) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}
void CSetGraph::print() {
    size_t counter = 0;
    for (auto i : vertices) {
        std::cout << "[" << counter++ << "]: ";
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
