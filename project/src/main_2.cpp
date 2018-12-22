//
// Created by Pavel Pupchin on 2018-12-05.
//

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <Generator.h>
#include <GraphGen.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <deque>
#include <utility>
#include <set>
#include <algorithm>
#include <queue>

struct IGraph {
    virtual ~IGraph() = default;

    virtual void addEdge(int from, int to, int distance) = 0;
    virtual int getEdgeDistance(int from, int to) = 0;
    virtual int verticesCount() const = 0;

    virtual std::vector<int> getNextVertices(int vertex) const = 0;

};

class Graph : public IGraph {
public:
    explicit Graph(int size) : adjacencyMap(static_cast<unsigned long>(size)) {}
    ~Graph() override = default;

    void addEdge(int from, int to, int distance) override;
    int getEdgeDistance(int from, int to) override;
    int verticesCount() const override;
    std::vector<int> getNextVertices(int vertex) const override;
    int getShortestWay(Graph &graph, int from, int to);

private:
    std::vector<std::map<int, int>> adjacencyMap;
    const int maxDistance = 2000000;

};

void Graph::addEdge(int from, int to, int distance) {
    auto temp = adjacencyMap[from].find(to);
    if (temp != adjacencyMap[from].end()) {
        if (temp->second > distance)
            temp->second = distance;
    } else {
        adjacencyMap[from].insert({to, distance});
        adjacencyMap[to].insert({from, distance});
    }
}

int Graph::getEdgeDistance(int from, int to) {
    auto temp = adjacencyMap[from].find(to);
    if (temp != adjacencyMap[from].end())
        return temp->second;
    return -1;
}

int Graph::verticesCount() const {
    return static_cast<int>(adjacencyMap.size());
}

std::vector<int> Graph::getNextVertices(int vertex) const {
    std::vector<int> tempVertices;
    for (const auto &i : adjacencyMap[vertex])
        tempVertices.push_back(i.first);
    return tempVertices;
}

int Graph::getShortestWay(Graph &graph, int from, int to) {
    std::vector<int> distances(static_cast<unsigned long>(graph.verticesCount()), maxDistance);
    distances[from] = 0;
    std::set<std::pair<int, int>> dijkstraTemp;
    dijkstraTemp.insert({distances[from], from});

    int max_size = 0;

    while (dijkstraTemp.size() > 0) {
        auto vertexTemp = dijkstraTemp.begin()->second;
        dijkstraTemp.erase(dijkstraTemp.begin());
        auto nextVertex = graph.getNextVertices(vertexTemp);

        (max_size < dijkstraTemp.size()) ? max_size = dijkstraTemp.size() : max_size = max_size;

        for (const auto &i : nextVertex) {
            auto edgeWeight = graph.getEdgeDistance(vertexTemp, i);
            if (distances[vertexTemp] + edgeWeight < distances[i]) {
                dijkstraTemp.erase({distances[i], i});
                distances[i] = distances[vertexTemp] + edgeWeight;
                dijkstraTemp.insert({distances[i], i});
            }
        }
    }

    std::cout << max_size << std::endl;
    return distances[to];
}
////////////////////////////

template <class T>
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

    // выбрать хранение
    std::vector<std::vector<std::pair<unsigned short, T>>> out_edges;
};

template <class T>
void Graph_weighted<T>::add_edge(unsigned short from, unsigned short to, T weight) {
    assert(from >= 0 && from < graph_size);
    assert(to >= 0 && to < graph_size);

    out_edges[from].emplace_back(to, weight);
    out_edges[to].emplace_back(from, weight);
}

template <class T>
std::vector<std::pair<unsigned short, T>> Graph_weighted<T>::get_next_vertices(unsigned short vertex) const {
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
    Edge(unsigned short from, unsigned short to, T weight) : vert_from(from), vert_to(to), weight(weight), priority(weight) {};
    Edge(unsigned short from, unsigned short to) : vert_from(from), vert_to(to), weight(0), priority(0) {};
    Edge(unsigned short from, unsigned short to, T weight, unsigned short priority) : vert_from(from), vert_to(to), weight(weight), priority(priority) {};

    unsigned short vert_from;
    unsigned short vert_to;
    T weight;
    unsigned short priority;
};

template <class T>
bool operator <(const Edge<T> &x, const Edge<T> &y) {
    return (x.priority != y.priority) ? x.priority <= y.priority : x.weight <= y.weight;
}

template <class T>
bool operator ==(const Edge<T> &x, const Edge<T> &y) {
    return std::tie(x.vert_to, x.vert_from, x.weight) == std::tie(y.vert_to, y.vert_from, y.weight);
}
template <class T>
void print_deque(std::deque<Edge<T>> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    for (size_t i = 0; i < queue.size(); i++)
        std::cout << "[" << i << "] = (f = " << queue[i].vert_from << ", t = " << queue[i].vert_to << ", w = "
                  << queue[i].weight << ", p = " << queue[i].priority << ")\n";
    std::cout << "===========" << std::endl;
}

template <class T>
void print_deque(std::set<Edge<T>> &queue) {
    std::cout << "===========\ndeque (" << queue.size() << ")\n";
    int i = 0;
    for (auto j : queue)
        std::cout << "[" << i++ << "] = (f = " << j.vert_from << ", t = " << j.vert_to << ", w = " << j.weight
                  << ", p = " << j.priority << ")\n";
    std::cout << "===========" << std::endl;
}

template <class T>
size_t dijkstra(const Graph_weighted<T> *graph, const int &begin, const int &end) {
    size_t graph_size = graph->get_size();
//    std::set<Edge<T>> deque;      //хранит все вершины и все для обработки
    std::set<Edge<T>> tmp_deque;    //

    int max_size = 0;

    std::vector<T> vertices_weights(graph_size, std::numeric_limits<T>::max());
    vertices_weights[begin] = 0;

    for (auto i : graph->get_next_vertices(begin))
        tmp_deque.emplace(begin, i.first, i.second);

    unsigned short tmp_from(0);
    unsigned short tmp_to(0);
    T tmp_weight(0);

    while (!tmp_deque.empty()) {
        (max_size < tmp_deque.size()) ? max_size = static_cast<int>(tmp_deque.size()) : max_size = max_size;

        print_deque(tmp_deque);

        tmp_from = tmp_deque.begin()->vert_from;
        tmp_to = tmp_deque.begin()->vert_to;
        tmp_weight = tmp_deque.begin()->weight;
        tmp_deque.erase(tmp_deque.begin());

        if (vertices_weights[tmp_to] > tmp_weight + vertices_weights[tmp_from]) {
            vertices_weights[tmp_to] = tmp_weight + vertices_weights[tmp_from];
            // можно еще хранить точки откуда, но в данной задаче излишне
            for (auto i : graph->get_next_vertices(tmp_to)) {
                if (i.first != tmp_from)
                    tmp_deque.emplace(tmp_to, i.first, i.second, i.second + vertices_weights[tmp_to]);
            }
        }
    }

    std::cout << "d = " << max_size << std::endl;
    return vertices_weights[end];
}

int main() {
    int numOfVertices = 0;
    int numOfEdges = 0;
    int from = 0;
    int to = 0;
    int distance = 0;
    int result = 0;

    std::cin >> numOfVertices >> numOfEdges;
    Graph graph(numOfVertices);
    Graph_weighted<unsigned short> graph2(static_cast<size_t>(numOfVertices), static_cast<size_t>(numOfEdges * numOfVertices));


    GraphGen gen;
    std::vector<std::pair<int, int>> rand_verts = gen.generate(numOfVertices, numOfVertices / numOfEdges);
    while (numOfEdges > 0) {
        std::cin >> from >> to >> distance;
        graph.addEdge(from, to, distance);
        graph2.add_edge(from, to, distance);
        numOfEdges--;
    }
//    int rand_weight;
//    for (auto i : rand_verts) {
//        rand_weight = rand_num<int>(0, 10000);
//        graph.addEdge(i.first, i.second, rand_weight);
//        graph2.add_edge(i.first, i.second, rand_weight);
//    }

    from = 0;
    to = 0;
    std::cin >> from >> to;
    result = graph.getShortestWay(graph, from, to);
    std::cout << result << std::endl;
    result = dijkstra<unsigned short>(&graph2, from, to);
    std::cout << result;

    return 0;
}