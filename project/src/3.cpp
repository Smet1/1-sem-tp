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

template<class T>
class Graph_weighted {
 public:
    Graph_weighted() : graph_size(0), edges_count(0), out_edges(0) {};
    Graph_weighted(size_t graph_size, size_t edges_count) : graph_size(graph_size), edges_count(edges_count),
                                                            out_edges(edges_count) {};
    ~Graph_weighted() = default;

    size_t get_size() const { return graph_size; };
    size_t get_edges_count() const { return edges_count; };
    void add_edge(unsigned short from, unsigned short to, T weight);

    std::vector<std::pair<unsigned short, T>> get_next_vertices(unsigned short vertex) const;
    void print();
 private:
    size_t graph_size;
    size_t edges_count;

    std::vector<std::vector<std::pair<unsigned short, T>>> out_edges;
};

template<class T>
void Graph_weighted<T>::add_edge(unsigned short from, unsigned short to, T weight) {
    //    assert(from >= 0 && from < graph_size);
    //    assert(to >= 0 && to < graph_size);
    //    assert(weight >= 0 && weight <= 10000);

    out_edges[from].emplace_back(to, weight);
    out_edges[to].emplace_back(from, weight);
}

template<class T>
std::vector<std::pair<unsigned short, T>> Graph_weighted<T>::get_next_vertices(unsigned short vertex) const {
    //    assert(vertex >= 0 && vertex < graph_size);

    return out_edges[vertex];
}

template<class T>
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

template<class T>
struct Edge {
    Edge() : vert_from(0), vert_to(0), weight(0) {};
    Edge(unsigned short from, unsigned short to, T weight)
        : vert_from(from), vert_to(to), weight(weight), priority(weight) {};
    Edge(unsigned short from, unsigned short to) : vert_from(from), vert_to(to), weight(0), priority(0) {};
    Edge(unsigned short from, unsigned short to, T weight, unsigned short priority) :
        vert_from(from), vert_to(to), weight(weight), priority(priority) {};

    unsigned short vert_from;
    unsigned short vert_to;
    T weight;
    unsigned short priority;
};

template<class T>
bool operator<(const Edge<T> &x, const Edge<T> &y) {
    return (x.priority != y.priority) ? x.priority <= y.priority : x.weight <= y.weight;
}

template<class T>
void print_deque(std::set<std::pair<T, unsigned short >> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    int i = 0;
    for (auto j : queue)
        std::cout << "[" << i++ << "] = (t = " << j.second << ", w = " << j.first << ")\n";
    std::cout << "===========" << std::endl;
}

template<class T>
void print_deque(std::set<Edge<T>> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    int i = 0;
    for (auto j : queue)
        std::cout << "[" << i++ << "] = (f = " << j.vert_from << ", t = " << j.vert_to << ", w = " << j.weight
                  << ", p = " << j.priority << ")\n";
    std::cout << "===========" << std::endl;
}

template<class T>
size_t dijkstra(const Graph_weighted<T> *graph, const int &begin, const int &end) {
    //    size_t graph_size = graph->get_size();
    //    std::set<Edge<T>> tmp_deque;
    //
    //    std::vector<T> vertices_weights(graph_size, std::numeric_limits<T>::max());
    //    vertices_weights[begin] = 0;
    //
    //    for (auto i : graph->get_next_vertices(begin))
    //        tmp_deque.emplace(begin, i.first, i.second);
    //
    //    size_t tmp_from(0);
    //    size_t tmp_to(0);
    //    T tmp_weight(0);
    //
    //    while (!tmp_deque.empty()) {
    //        tmp_from = tmp_deque.begin()->vert_from;
    //        tmp_to = tmp_deque.begin()->vert_to;
    //        tmp_weight = tmp_deque.begin()->weight;
    //        tmp_deque.erase(tmp_deque.begin());
    //
    //        if (vertices_weights[tmp_to] > tmp_weight + vertices_weights[tmp_from]) {
    //            vertices_weights[tmp_to] = tmp_weight + vertices_weights[tmp_from];
    //            // можно еще хранить точки откуда, но в данной задаче излишне
    //            for (auto i : graph->get_next_vertices(tmp_to)) {
    //                if (i.first != tmp_from)
    //                    tmp_deque.emplace(tmp_to, i.first, i.second, i.second + vertices_weights[tmp_to]);
    //                    // + vertices_weights[tmp_from] чтобы правильно работал сет
    //            }
    //        }
    //    }

    size_t graph_size = graph->get_size();
    std::set<std::pair<T, unsigned short>> tmp_deque;  // иначе очередь не работает, только с парами

    std::vector<T> vertices_weights(graph_size, std::numeric_limits<T>::max());
    unsigned short tmp_from(0);
    unsigned short tmp_to(0);
    T tmp_weight(0);
    vertices_weights[begin] = 0;

    tmp_deque.emplace(0, begin);

    while (!tmp_deque.empty()) {
        print_deque(tmp_deque);
        tmp_from = tmp_deque.begin()->second;
        //        tmp_weight = tmp_deque.begin()->first;
        tmp_deque.erase(tmp_deque.begin());

        for (auto vert : graph->get_next_vertices(tmp_from)) {
            if (vertices_weights[vert.first] > vert.second + vertices_weights[tmp_from]) {
                tmp_deque.erase(std::make_pair(vertices_weights[tmp_from], vert.first));

                vertices_weights[vert.first] = vert.second + vertices_weights[tmp_from];

                tmp_deque.insert(std::make_pair(vertices_weights[vert.first], vert.first));
            }
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
    //    assert(vert_count >= 0 && vert_count <= 10000);

    std::cin >> edges_count;
    //    assert(edges_count >= 0 && edges_count <= 250000);

    Graph_weighted<unsigned short> graph(static_cast<size_t>(vert_count), static_cast<size_t>(edges_count));

    for (size_t i = 0; i < edges_count; ++i) {
        std::cin >> from;  // asserting vals in add_edge()
        std::cin >> to;
        std::cin >> weight;

        graph.add_edge(from, to, weight);
        //        graph.add_edge(to, from, weight);
    }

    std::cin >> vertex_from;
    //    assert(vertex_from >= 0 && vertex_from <= vert_count);

    std::cin >> vertex_to;
    //    assert(vertex_to >= 0 && vertex_to <= vert_count);

    //    graph.print();

    // run dijkstra
    size_t weight_route = dijkstra<unsigned short>(&graph, vertex_from, vertex_to);
    std::cout << weight_route;

    return 0;
}

/*
7 11
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
5 6 1
6 1 1
2 0
 */