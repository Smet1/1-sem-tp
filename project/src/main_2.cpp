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

    while (dijkstraTemp.size() > 0) {
        auto vertexTemp = dijkstraTemp.begin()->second;
        dijkstraTemp.erase(dijkstraTemp.begin());
        auto nextVertex = graph.getNextVertices(vertexTemp);
        for (const auto &i : nextVertex) {
            auto edgeWeight = graph.getEdgeDistance(vertexTemp, i);
            if (distances[vertexTemp] + edgeWeight < distances[i]) {
                dijkstraTemp.erase({distances[i], i});
                distances[i] = distances[vertexTemp] + edgeWeight;
                dijkstraTemp.insert({distances[i], i});
            }
        }
    }
    return distances[to];
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

    while (numOfEdges > 0) {
        std::cin >> from >> to >> distance;
        graph.addEdge(from, to, distance);
        numOfEdges--;
    }

    from = 0;
    to = 0;
    std::cin >> from >> to;
    result = graph.getShortestWay(graph, from, to);
    std::cout << result;

    return 0;
}