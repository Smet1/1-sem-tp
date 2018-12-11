//
// Created by Kirill Smetankin on 10/12/2018.
//
#include <CListGraph.hpp>

#include <assert.h>
#include <iostream>

ListGraph::ListGraph(size_t vertices_count) : out_edges_(vertices_count), in_edges_(vertices_count) {}

void ListGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < vertices_count());
    assert(to >= 0 && to < vertices_count());

    // No checks (multigraph)
    out_edges_[from].push_back(to);
    in_edges_[to].push_back(from);
}

size_t ListGraph::vertices_count() const {
    return out_edges_.size();
}

std::vector<int> ListGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());
    return out_edges_[vertex];
}

std::vector<int> ListGraph::get_prev_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());
    return in_edges_[vertex];
}

void ListGraph::print(std::ostream &out) {
    for (int i = 0; i < out_edges_.size(); ++i) {
        out << i << ": ";
        for (int out_target : out_edges_[i]) {
            out << out_target << " ";
        }

        out << std::endl;
    }
}
