//
// Created by Kirill Smetankin on 2018-12-17.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <deque>
#include <utility>
#include <set>
#include <algorithm>
#include <queue>

template <class T>
class Graph_weighted {
 public:
    Graph_weighted() : graph_size(0), edges_count(0), out_edges(0) {};
    Graph_weighted(size_t graph_size, size_t edges_count) : graph_size(graph_size), edges_count(edges_count),
                                                   out_edges(edges_count) {};
    ~Graph_weighted() = default;

    size_t get_size() const { return graph_size; };
    size_t get_edges_count() const { return edges_count; };
    void add_edge(int from, int to, T weight);

    std::vector<std::pair<int, T>> get_next_vertices(int vertex) const;
    void print();
 private:
    size_t graph_size;
    size_t edges_count;

    std::vector<std::vector<std::pair<int, T>>> out_edges;
};

template <class T>
void Graph_weighted<T>::add_edge(int from, int to, T weight) {
    assert(from >= 0 && from < graph_size);
    assert(to >= 0 && to < graph_size);
    assert(weight >= 0 && weight <= 10000);

    out_edges[from].emplace_back(to, weight);
    out_edges[to].emplace_back(from, weight);
}

template <class T>
std::vector<std::pair<int, T>> Graph_weighted<T>::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < graph_size);

    return out_edges[vertex];
}

template <class T>
void Graph_weighted<T>::print() {
    for (int i = 0; i < graph_size; ++i) {
        std::cout << i << ": ";
        for (auto out_target : out_edges[i]) {
            std::cout << "(" << out_target.first << ", w = " << out_target.second << "); ";
        }

        std::cout << std::endl;
    }
}

void print_deque(std::deque<std::pair<int, int>> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    for (size_t i = 0; i < queue.size(); i++)
        std::cout << "[" << i << "] = (" << queue[i].first << ", " << queue[i].second << ")\n";
    std::cout << "===========" << std::endl;
}

void print_deque(std::deque<int> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    for (size_t i = 0; i < queue.size(); i++)
        std::cout << "[" << i << "] = (" << queue[i] << ")\n";
    std::cout << "===========" << std::endl;
}

template <class T>
struct Edge {
    Edge() : vert_from(0), vert_to(0), weight(0) {};
    Edge(size_t from, size_t to, T weight) : vert_from(from), vert_to(to), weight(weight) {};
    Edge(size_t from, size_t to) : vert_from(from), vert_to(to) {};

    size_t vert_from;
    size_t vert_to;
    T weight;
};

template <class T>
void print_deque(std::deque<Edge<T>> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    for (size_t i = 0; i < queue.size(); i++)
        std::cout << "[" << i << "] = (f = " << queue[i].vert_from << ", t = " << queue[i].vert_to << ", w = " << queue[i].weight << ")\n";
    std::cout << "===========" << std::endl;
}

// TODO(): восстанавливать путь, а не брать макс в массиве (непрвильный ответ)
// TODO(): при отсутсвии маршрута не работает (скорее всего проблема в пред пункте)

template <class T>
size_t dijkstra(const Graph_weighted<T> *graph, const int &begin, const int &end) {
    size_t graph_size = graph->get_size();
    std::deque<Edge<T>> deque;
    std::deque<Edge<T>> tmp_deque;

    std::set<int> visited;

//    std::vector<T> vertices_weights(graph_size, graph->get_edges_count() + 1);
    std::vector<T> vertices_weights(graph_size, std::numeric_limits<T>::max());
    vertices_weights[begin] = 0;

    for (auto i : graph->get_next_vertices(begin))
        deque.emplace_back(begin, i.first, i.second);

//    print_deque(deque);

    int tmp_from(0);
    int tmp_to(0);
    T tmp_weight(0);
    int wave_num(1);

    while (!deque.empty()) {
//        std::cout << "wave_num = " << wave_num << std::endl;
//        print_deque(deque);

        tmp_from = deque.front().vert_from;
        tmp_to = deque.front().vert_to;
        tmp_weight = deque.front().weight;
        deque.pop_front();

        if (vertices_weights[tmp_to] > tmp_weight) {
            vertices_weights[tmp_to] = tmp_weight + vertices_weights[tmp_from];
            // можно еще хранить точки откуда, но в данной задаче излишне
        }

        if (visited.find(tmp_to) == visited.end()) {
            for (auto i : graph->get_next_vertices(tmp_to)) {
                tmp_deque.emplace_back(tmp_to, i.first, i.second);
            }
            visited.insert(tmp_to);
        }

        if (deque.empty()) {
            ++wave_num;
            deque = tmp_deque;
            tmp_deque.clear();
        }
    }

    return vertices_weights[end];
}

int main() {
    int vert_count(0);
    int edges_count(0);
    int vertex_from(0), vertex_to(0);
    int from(0), to(0), weight(0);

    std::cin >> vert_count;
    assert(vert_count >= 0 && vert_count <= 10000);

    std::cin >> edges_count;
    assert(edges_count >= 0 && edges_count <= 250000);

    Graph_weighted<int> graph(static_cast<size_t>(vert_count), static_cast<size_t>(edges_count));

    for (size_t i = 0; i < edges_count; ++i) {
        std::cin >> from;  // asserting vals in add_edge()
        std::cin >> to;
        std::cin >> weight;

        graph.add_edge(from, to, weight);
//        graph.add_edge(to, from, weight);
    }

    std::cin >> vertex_from;
    assert(vertex_from >= 0 && vertex_from <= vert_count);

    std::cin >> vertex_to;
    assert(vertex_to >= 0 && vertex_to <= vert_count);

//    graph.print();

    // run dijkstra
    size_t weight_route = dijkstra<int>(&graph, vertex_from, vertex_to);
    std::cout << weight_route;

    return 0;
}