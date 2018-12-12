//
// Created by Kirill Smetankin on 12/12/2018.
//

#include <iostream>
#include <vector>
#include <cassert>

template <class T>
class Graph {
 public:
    Graph() : graph_size(0), out_edges(0), in_edges(0) {};
    Graph(size_t graph_size, size_t edges_count) : graph_size(graph_size), out_edges(edges_count), in_edges(edges_count) {};
    ~Graph() = default;

    size_t get_size() const { return graph_size; };
    void add_edge(T from, T to);

    std::vector<T> get_next_vertices(int vertex);
 private:
    size_t graph_size;

    std::vector<std::vector<T>> out_edges;
    std::vector<std::vector<T>> in_edges;
};
template<class T>
void Graph<T>::add_edge(T from, T to) {
    assert(from >= 0 && from < graph_size);
    assert(to >= 0 && to < graph_size);

    out_edges[from].push_back(to);
    in_edges[to].push_back(from);
}
template<class T>
std::vector<T> Graph<T>::get_next_vertices(int vertex) {
    assert(vertex >= 0 && vertex < graph_size);

    return out_edges[vertex];
}

int main() {
    int vert_count(0);
    int edges_count(0);
    int vertex_from(0), vertex_to(0);
    int from(0), to(0);

    std::cin >> vert_count;
    assert(vert_count >= 0 && vert_count <= 50000);

    std::cin >> edges_count;
    assert(edges_count >= 0 && edges_count <= 200000);

    Graph<int> graph(static_cast<size_t>(vert_count), static_cast<size_t>(edges_count));

    for (size_t i = 0; i < edges_count; ++i) {
        std::cin >> from;  // asserting vals in add_edge()
        std::cin >> to;

        graph.add_edge(from, to);
    }

    std::cin >> vertex_from;
    assert(vertex_from >= 0 && from <= vertex_from);

    std::cin >> vertex_to;
    assert(vertex_to >= 0 && to <= vertex_to);

    // run dijkstra

    return 0;
}