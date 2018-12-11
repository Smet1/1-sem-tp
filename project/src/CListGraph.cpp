//
// Created by Kirill Smetankin on 10/12/2018.
//
#include <CListGraph.hpp>

#include <assert.h>
#include <iostream>

CListGraph::CListGraph(size_t vertices_count) : out_edges_(vertices_count), in_edges_(vertices_count) {}

void CListGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < vertices_count());
    assert(to >= 0 && to < vertices_count());

    // No checks (multigraph)
    out_edges_[from].push_back(to);
    in_edges_[to].push_back(from);
}

size_t CListGraph::vertices_count() const {
    return out_edges_.size();
}

std::vector<int> CListGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());
    return out_edges_[vertex];
}

std::vector<int> CListGraph::get_prev_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());
    return in_edges_[vertex];
}

void CListGraph::print(std::ostream &out) {
    for (int i = 0; i < out_edges_.size(); ++i) {
        out << i << ": ";
        for (int out_target : out_edges_[i]) {
            out << out_target << " ";
        }

        out << std::endl;
    }
}
CListGraph::CListGraph(const IGraph *graph) {
    std::vector<int> temp;
    for (auto i = 0; i < graph->vertices_count(); ++i) {
        temp = graph->get_next_vertices(i);

        for (auto x : temp) {
            add_edge(i, x);
        }
    }
}
