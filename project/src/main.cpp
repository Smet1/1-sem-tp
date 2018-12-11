//
// Created by Kirill Smetankin on 11/12/2018.
//

#include <CListGraph.hpp>
#include <CMatrixGraph.hpp>
#include <CArcGraph.hpp>
#include <CSetGraph.hpp>
#include <GraphGen.hpp>

#include <iostream>
#include <chrono>

// TODO(): генератор графов (±)
// TODO(): тесты
// TODO(): время работы (±)
// TODO(): ассерты
// TODO(): размер графов

const int graph_size = 100;

int main() {
    std::cout << "graph_size = " << graph_size << std::endl;
    Timer timer;

    timer.set_begin();
    GraphGen gen;
    std::vector<std::pair<int, int>> rand_verts = gen.generate(graph_size);
    timer.set_end();
    timer.calculate("Generation");

    std::cout << "edges_count = " << rand_verts.size() << std::endl;

    std::cout << "<========- CHECKING NEXT VERTICES -========>" << std::endl;

    size_t counter = 0;
//    for (auto i : rand_verts) {
////        std::cout << "[" << counter++ << "]: (" << i.first << ", " << i.second << ")" << std::endl;
//        if (i.first == 0)
//            std::cout << "[" << counter++ << "]: (" << i.first << ", " << i.second << ")" << std::endl;
//    }

    ///////////////////////////////////////////////
    std::cout << "CListGraph\n";

    timer.set_begin();
    CListGraph graph(graph_size);
    for (auto i : rand_verts) {
        graph.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate("CListGraph adding edges");
    std::cout << "--Vertices count = " << graph.vertices_count() << std::endl;

    timer.set_begin();
    std::vector<int> front_vertices = graph.get_next_vertices(0);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from begin");

    timer.set_begin();
    front_vertices = graph.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from middle");

    timer.set_begin();
    front_vertices = graph.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from back");
//    std::cout << "--Out edges for a vertex 0 = ";
//    for (int front : front_vertices) {
//        std::cout << "(0, " << front << "), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CMatrixGraph\n";

    timer.set_begin();
    CMatrixGraph graph1(graph_size);
    for (auto i : rand_verts) {
        graph1.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate("CMatrixGraph adding edges");
    std::cout << "--Vertices count = " << graph1.vertices_count() << std::endl;

    timer.set_begin();
    front_vertices = graph1.get_next_vertices(0);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from begin");

    timer.set_begin();
    front_vertices = graph1.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from middle");

    timer.set_begin();
    front_vertices = graph1.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from back");
//    std::cout << "--Out edges for a vertex 0 = ";
//    for (int front : front_vertices) {
//        std::cout << "(0, " << front << "), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CSetGraph\n";

    timer.set_begin();
    CSetGraph graph2(graph_size);
    for (auto i : rand_verts) {
        graph2.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate("CSetGraph adding edges");

    std::cout << "--Vertices count = " << graph2.vertices_count() << std::endl;

    timer.set_begin();
    front_vertices = graph2.get_next_vertices(0);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from begin");

    timer.set_begin();
    front_vertices = graph2.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from middle");

    timer.set_begin();
    front_vertices = graph2.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from back");
//    std::cout << "--Out edges for a vertex 0 = ";
//    for (int front : front_vertices) {
//        std::cout << "(0, " << front << "), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CArcGraph\n";

    timer.set_begin();
    CArcGraph graph3(graph_size);
    for (auto i : rand_verts) {
        graph3.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate("CArcGraph adding edges");

    std::cout << "--Vertices count = " << graph3.vertices_count() << std::endl;

    timer.set_begin();
    front_vertices = graph3.get_next_vertices(0);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from begin");

    timer.set_begin();
    front_vertices = graph3.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from middle");

    timer.set_begin();
    front_vertices = graph3.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from back");
//    std::cout << "--Out edges for a vertex 0 = ";
//    for (int front : front_vertices) {
//        std::cout << "(0, " << front << "), ";
//    }
//    std::cout << std::endl;

    ///////////////////////////////////////////////

    std::cout << std::endl << "<========- CHECKING PREV VERTICES -========>" << std::endl;

    counter = 0;
//    for (auto i : rand_verts) {
//        if (i.second == 1)
//            std::cout << "[" << counter++ << "]: (" << i.first << ", " << i.second << ")" << std::endl;
//    }
    ///////////////////////////////////////////////

//    std::cout << "--Vertices count = " << graph.vertices_count() << std::endl;
    std::cout << "CListGraph" << std::endl;

    timer.set_begin();
    std::vector<int> prev_vertices = graph.get_prev_vertices(0);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from begin");

    timer.set_begin();
    prev_vertices = graph.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from middle");

    timer.set_begin();
    prev_vertices = graph.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CListGraph get_next_vertices from back");
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CMatrixGraph" << std::endl;

    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(0);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from begin");

    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from begin");

    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CMatrixGraph get_next_vertices from begin");
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CSetGraph" << std::endl;

    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(0);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from begin");

    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from middle");

    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CSetGraph get_next_vertices from back");
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
    ///////////////////////////////////////////////
    std::cout << "CArcGraph" << std::endl;

    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(0);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from begin");

    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from middle");

    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate("CArcGraph get_next_vertices from back");
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//    std::cout << "<============- CListGraph -============>\n";
//
//    CListGraph graph(4);
//    graph.add_edge(0, 1);
//    graph.add_edge(0, 3);
//    graph.add_edge(2, 3);
//    graph.add_edge(2, 0);
//    graph.add_edge(1, 3);
//    graph.add_edge(3, 1);
//
//    std::cout << "--Vertices count = " << graph.vertices_count() << std::endl;
//
//    std::vector<int> prev_vertices = graph.get_prev_vertices(1);
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//
//    std::vector<int> front_vertices = graph.get_next_vertices(2);
//    std::cout << "--Out edges for a vertex 2 = ";
//    for (int front : front_vertices) {
//        std::cout << "(2, " << front << "), ";
//    }
//    std::cout << std::endl;
//
//    std::cout << std::endl << "--print:" << std::endl;
//    graph.print(std::cout);
//
//    /////////////////////////////
//    std::cout << "<============- CMatrixGraph -============>\n";
//
//    CMatrixGraph cMatrixGraph(4);
//    cMatrixGraph.add_edge(0, 1);
//    cMatrixGraph.add_edge(0, 3);
//    cMatrixGraph.add_edge(2, 3);
//    cMatrixGraph.add_edge(2, 0);
//    cMatrixGraph.add_edge(1, 3);
//    cMatrixGraph.add_edge(3, 1);
//
//    std::cout << "Vertices count = " << cMatrixGraph.vertices_count() << std::endl;
//
//    prev_vertices = cMatrixGraph.get_prev_vertices(1);
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//
//    front_vertices = cMatrixGraph.get_next_vertices(2);
//    std::cout << "--Out edges for a vertex 2 = ";
//    for (int front : front_vertices) {
//        std::cout << "(2, " << front << "), ";
//    }
//    std::cout << std::endl;
//
//    std::cout << std::endl << "--print:" << std::endl;
//    cMatrixGraph.print();
//
//    /////////////////////////////
//    std::cout << "<============- CArcGraph -============>\n";
//
//    CArcGraph cArcGraph(4);
//    cArcGraph.add_edge(0, 1);
//    cArcGraph.add_edge(0, 3);
//    cArcGraph.add_edge(2, 3);
//    cArcGraph.add_edge(2, 0);
//    cArcGraph.add_edge(1, 3);
//    cArcGraph.add_edge(3, 1);
//
//    std::cout << "Vertices count = " << cArcGraph.vertices_count() << std::endl;
//
//    prev_vertices = cArcGraph.get_prev_vertices(1);
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//
//    front_vertices = cArcGraph.get_next_vertices(2);
//    std::cout << "--Out edges for a vertex 2 = ";
//    for (int front : front_vertices) {
//        std::cout << "(2, " << front << "), ";
//    }
//    std::cout << std::endl;
//
//    std::cout << std::endl << "--print:" << std::endl;
//    cArcGraph.print();
//
//    std::cout << "<============- CArcGraph.constr_test -============>\n";
//
//    CArcGraph cArcGraph_1(&graph);
//
//    std::cout << "Vertices count = " << cArcGraph_1.vertices_count() << std::endl;
//
//    prev_vertices = cArcGraph_1.get_prev_vertices(1);
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//
//    front_vertices = cArcGraph_1.get_next_vertices(2);
//    std::cout << "--Out edges for a vertex 2 = ";
//    for (int front : front_vertices) {
//        std::cout << "(2, " << front << "), ";
//    }
//    std::cout << std::endl;
//
//    std::cout << std::endl << "--print:" << std::endl;
//    cArcGraph_1.print();
//    /////////////////////////////
//    std::cout << "<============- CSetGraph -============>\n";
//
//    CSetGraph cSetGraph(4);
//    cSetGraph.add_edge(0, 1);
//    cSetGraph.add_edge(0, 3);
//    cSetGraph.add_edge(2, 3);
//    cSetGraph.add_edge(2, 0);
//    cSetGraph.add_edge(1, 3);
//    cSetGraph.add_edge(3, 1);
//
//    std::cout << "Vertices count = " << cSetGraph.vertices_count() << std::endl;
//
//    prev_vertices = cSetGraph.get_prev_vertices(1);
//    std::cout << "--In edges for a vertex 1 = ";
//    for (int prev : prev_vertices) {
//        std::cout << "(" << prev << ", 1), ";
//    }
//    std::cout << std::endl;
//
//    front_vertices = cSetGraph.get_next_vertices(2);
//    std::cout << "--Out edges for a vertex 2 = ";
//    for (int front : front_vertices) {
//        std::cout << "(2, " << front << "), ";
//    }
//    std::cout << std::endl;
//
//    std::cout << std::endl << "--print:" << std::endl;
//    cSetGraph.print();

    return 0;
}