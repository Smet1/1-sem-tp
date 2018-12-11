//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CSetGraph.hpp>

void CSetGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < vertices_count());
    assert(to >= 0 && to < vertices_count());

    vertices[from].insert(to);
}

size_t CSetGraph::vertices_count() const {
    return vertices_size;
}

std::vector<int> CSetGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());

    return std::vector<int>(vertices[vertex].begin(), vertices[vertex].end());
}

std::vector<int> CSetGraph::get_prev_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());

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

CSetGraph::CSetGraph(const IGraph *graph) : vertices_size(graph->vertices_count()) {
    vertices.clear();

    std::vector<int> temp;
    for (auto i = 0; i < graph->vertices_count(); ++i) {
        temp = graph->get_next_vertices(i);

        for (auto x : temp) {
            add_edge(i, x);
        }
    }
}
