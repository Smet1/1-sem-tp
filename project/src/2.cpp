//
// Created by Kirill Smetankin on 12/12/2018.
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
class Graph {
 public:
    Graph() : graph_size(0), out_edges(0) {};
    Graph(size_t graph_size, size_t edges_count) : graph_size(graph_size), edges_count(edges_count),
                                                   out_edges(edges_count) {};
    ~Graph() = default;

    size_t get_size() const { return graph_size; };
    size_t get_edges_count() const { return edges_count; };
    void add_edge(T from, T to);

    std::vector<T> get_next_vertices(int vertex) const;
    void print();
 private:
    size_t graph_size;
    size_t edges_count;

    std::vector<std::vector<T>> out_edges;
};

template<class T>
void Graph<T>::add_edge(T from, T to) {
    assert(from >= 0 && from < graph_size);
    assert(to >= 0 && to < graph_size);

    out_edges[from].push_back(to);
    out_edges[to].push_back(from);

}

template<class T>
std::vector<T> Graph<T>::get_next_vertices(int vertex) const {
    assert(vertex >= 0 && vertex < graph_size);

    return out_edges[vertex];
}

template<class T>
void Graph<T>::print() {
    for (int i = 0; i < graph_size; ++i) {
        std::cout << i << ": ";
        for (int out_target : out_edges[i]) {
            std::cout << out_target << " ";
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

// TODO(): восстанавливать путь, а не брать макс в массиве (непрвильный ответ)
// TODO(): при отсутсвии маршрута не работает (скорее всего проблема в пред пункте)

template <class T>
size_t dijkstra(const Graph<T> *graph, const int &begin, const int &end) {
    size_t size_graph = graph->get_size();
    std::deque<std::pair<int, int>> queue;
    std::deque<std::pair<int, int>> tmp_queue;  // чтобы контролировать номер волны
    std::set<int> visited;

    std::vector<int> vertices_weights(size_graph, static_cast<const int &>(graph->get_edges_count() + 1));
    std::vector<std::vector<int>> verts_from(size_graph);  // вершины откуда пришли в текущую по минимальному весу
    std::vector<unsigned short> temp = graph->get_next_vertices(begin);

    for (auto i : temp) {
//        std::cout << i << " ";
        queue.emplace_back(begin, i);
    }
//    std::cout << std::endl;
//    print_deque(queue);

    vertices_weights[begin] = 0;

    int tmp_from = 0;
    int tmp_to = 0;
    int wave_num = 1;
    while (!queue.empty()) {
//        std::cout << "wave_num = " << wave_num << std::endl;
//        print_deque(queue);

        tmp_from = queue.front().first;
        tmp_to = queue.front().second;
        queue.pop_front();

//        if (visited.find(tmp_to) != visited.end()) {
//            continue;
//        } else {
//            visited.insert(tmp_to);
//        }

        if (vertices_weights[tmp_to] > wave_num) {
            vertices_weights[tmp_to] = wave_num;
            verts_from[tmp_to].clear();
            verts_from[tmp_to].push_back(tmp_from);
        } else if (vertices_weights[tmp_to] == wave_num) {
            verts_from[tmp_to].push_back(tmp_from);
        }

        if (visited.find(tmp_to) == visited.end()) {
            for (auto i : graph->get_next_vertices(tmp_to)) {
                tmp_queue.emplace_back(tmp_to, i);
            }
            visited.insert(tmp_to);
        }

        if (queue.empty()) {
            queue = tmp_queue;
            tmp_queue.clear();
            ++wave_num;
            if (!verts_from[end].empty()) {
                // если кратчайшие пути найдены, следующие уже будут с большим весом
                break;
            }
        }
    }

//    std::cout << std::endl;

    size_t max = 0;
//    for (auto i : verts_from) {
//        max = std::max(max, i.size());
//    }

    if (verts_from[end].empty())
        return 0;
    else {
        std::deque<int> tmp;
        std::deque<int> routes;
        for (auto i : verts_from[end])
            routes.push_back(i);

        max = routes.size();

        while (!routes.empty()) {
            for (auto j : routes) {
                for (auto k : verts_from[j])
                    tmp.push_back(k);
            }

//            print_deque(routes);
//            print_deque(tmp);

            routes = tmp;
            tmp.clear();

            max = (max < routes.size()) ? routes.size() : max;
        }

    }

    return max;
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

    Graph<unsigned short> graph(static_cast<size_t>(vert_count), static_cast<size_t>(edges_count));

    for (size_t i = 0; i < edges_count; ++i) {
        std::cin >> from;  // asserting vals in add_edge()
        std::cin >> to;

        graph.add_edge(static_cast<unsigned short>(from), static_cast<unsigned short>(to));
    }

    std::cin >> vertex_from;
    assert(vertex_from >= 0 && vertex_from <= vert_count);

    std::cin >> vertex_to;
    assert(vertex_to >= 0 && vertex_to <= vert_count);

//    graph.print();

    // run dijkstra
    size_t routes_count = dijkstra<unsigned short >(&graph, vertex_from, vertex_to);
    std::cout << routes_count;

    return 0;
}