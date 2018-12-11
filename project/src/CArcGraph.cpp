//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CArcGraph.hpp>

void CArcGraph::add_edge(int from, int to) {
    vertices_mas.emplace_back(from, to);
}

size_t CArcGraph::vertices_count() const {
    std::set<int> vertices;

    for (auto vert : vertices_mas) {
        vertices.insert(vert.first);
        vertices.insert(vert.second);
    }

    return vertices.size();
}
std::vector<int> CArcGraph::get_next_vertices(int vertex) const {
    std::vector<int> next_vertices;

    for (auto i : vertices_mas) {
        if (i.first == vertex)
            next_vertices.push_back(i.second);
    }
    return next_vertices;
}
std::vector<int> CArcGraph::get_prev_vertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (auto i : vertices_mas) {
        if (i.second == vertex)
            prev_vertices.push_back(i.first);
    }
    return prev_vertices;
}
void CArcGraph::print() {
    size_t counter = 0;
    for (auto i : vertices_mas) {
        std::cout << "[" << counter++ << "]: (" << i.first << ", " << i.second << ")" << std::endl;
    }
}
CArcGraph::CArcGraph(const IGraph *graph) {
    std::vector<int> temp;
    for (auto i = 0; i < graph->vertices_count(); ++i) {
        temp = graph->get_next_vertices(i);

        for (auto x : temp) {
            add_edge(i, x);
        }
    }
}
