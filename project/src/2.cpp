//
// Created by Kirill Smetankin on 12/12/2018.
//

#include <iostream>
#include <vector>
#include <cassert>

template <class T>
class Graph {
 public:
    Graph();
    Graph(size_t graph_size);
    ~Graph() = default;

    size_t get_size();
    void add_edge(T from, T to);

    std::vector<T> get_next_vertices(int vertex);
 private:
    size_t graph_size;

    std::vector<std::vector<T>> out_edges;
    std::vector<std::vector<T>> in_edges;
};

int main() {
    int vert_count(0);
    int edges_count(0);
    int vertex_from(0), vertex_to(0);
    int from(0), to(0);

    std::cin >> vert_count;
    assert(vert_count >= 0 && vert_count <= 50000);

    std::cin >> edges_count;
    assert(edges_count >= 0 && edges_count <= 200000);

    Graph<int> graph(static_cast<size_t>(vert_count));

    for (size_t i = 0; i < edges_count; ++i) {
        std::cin >> from;
        assert(from >= 0 && from <= vert_count);

        std::cin >> to;
        assert(to >= 0 && to <= vert_count);

        graph.add_edge(from, to);
    }

    std::cin >> vertex_from;
    assert(vertex_from >= 0 && from <= vertex_from);

    std::cin >> vertex_to;
    assert(vertex_to >= 0 && to <= vertex_to);

    // run dijkstra

    return 0;
}