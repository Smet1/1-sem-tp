//
// Created by Kirill Smetankin on 10/12/2018.
//
#include <CListGraph.hpp>

#include <assert.h>
#include <iostream>

CListGraph::CListGraph(size_t vertices_count) : out_edges(vertices_count), in_edges(vertices_count), vertices_size(vertices_count) {}

void CListGraph::add_edge(int from, int to) {
    assert(from >= 0 && from < vertices_count());
    assert(to >= 0 && to < vertices_count());

    out_edges[from].push_back(to);
    in_edges[to].push_back(from);
}

size_t CListGraph::vertices_count() const {
    return out_edges.size();
}

std::vector<int> CListGraph::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());

    return out_edges[vertex];
}

std::vector<int> CListGraph::get_prev_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices_count());

    return in_edges[vertex];
}

void CListGraph::print(std::ostream &out) {
    for (int i = 0; i < out_edges.size(); ++i) {
        out << i << ": ";
        for (int out_target : out_edges[i]) {
            out << out_target << " ";
        }

        out << std::endl;
    }
}
CListGraph::CListGraph(const IGraph *graph) : vertices_size(graph->vertices_count()) {
    in_edges.clear();
    out_edges.clear();

    std::vector<int> temp;
    for (auto i = 0; i < graph->vertices_count(); ++i) {
        temp = graph->get_next_vertices(i);

        for (auto x : temp) {
            add_edge(i, x);
        }
    }
}
