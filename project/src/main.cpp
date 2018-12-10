//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CListGraph.hpp>
#include <CMatrixGraph.hpp>

#include <iostream>

int main() {
    std::cout << "<============- CListGraph -============>\n";

    ListGraph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 3);
    graph.add_edge(2, 3);
    graph.add_edge(2, 0);
    graph.add_edge(1, 3);
    graph.add_edge(3, 1);

    std::cout << "Vertices count = " << graph.vertices_count() << std::endl;
    std::vector<int> prev_vertices = graph.get_prev_vertices(1);
    std::cout << "In edges for a vertex 1 = ";
    for (int prev : prev_vertices) {
        std::cout << "(" << prev << ", 1), ";
    }
    std::cout << std::endl;

    graph.print(std::cout);

    /////////////////////////////
    std::cout << "<============- CMatrixGraph -============>\n";

    CMatrixGraph cMatrixGraph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 3);
    graph.add_edge(2, 3);
    graph.add_edge(2, 0);
    graph.add_edge(1, 3);
    graph.add_edge(3, 1);

    std::cout << "Vertices count = " << graph.vertices_count() << std::endl;

    return 0;
}