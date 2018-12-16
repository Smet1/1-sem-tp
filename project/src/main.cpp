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
#include <Generator.h>
#include <iomanip>

// TODO(): генератор графов (±)
// TODO(): тесты
// TODO(): время работы (±)
// TODO(): ассерты
// TODO(): размер графов


// TODO(): RPS для каждого метода (+)

const int graph_size = 100;
const int rps_iter = 1000;

int main() {
    std::cout << std::fixed << std::setprecision(3) << "graph_size = " << graph_size << std::endl;
    Timer timer;

    std::cout << "Generation\n";
    timer.set_begin();
    GraphGen gen;
//    Generator gen;
    std::vector<std::pair<int, int>> rand_verts = gen.generate(graph_size, 70);
//    std::vector<std::pair<int, int>> rand_verts = gen.generator(graph_size);

    timer.set_end();
    timer.calculate();

    std::cout << "edges_count = " << rand_verts.size() << std::endl;

    std::cout << "<========- CHECKING NEXT VERTICES -========>" << std::endl;

    size_t counter = 0;

    ///////////////////////////////////////////////
    std::cout << "CListGraph\n";

    timer.set_begin();
    CListGraph graph(graph_size);

    std::cout << "\tCListGraph adding edges:\n";
    for (auto i : rand_verts) {
        graph.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate();
    std::cout << "\t--Vertices count = " << graph.vertices_count() << std::endl;

    std::vector<int> front_vertices;

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from begin:\n";
    timer.set_begin();
    front_vertices = graph.get_next_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph.get_next_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from middle:\n";
    timer.set_begin();
    front_vertices = graph.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph.get_next_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from back:\n";
    timer.set_begin();
    front_vertices = graph.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph.get_next_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);
    ///////////////////////////////////////////////
    std::cout << "CMatrixGraph\n";

    std::cout << "\tCMatrixGraph adding edges:\n";
    timer.set_begin();
    CMatrixGraph graph1(graph_size);
    for (auto i : rand_verts) {
        graph1.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate();
    std::cout << "\t--Vertices count = " << graph1.vertices_count() << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from begin:\n";
    timer.set_begin();
    front_vertices = graph1.get_next_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph1.get_next_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from middle:\n";
    timer.set_begin();
    front_vertices = graph1.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph1.get_next_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from back:\n";
    timer.set_begin();
    front_vertices = graph1.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph1.get_next_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);
    ///////////////////////////////////////////////
    std::cout << "CSetGraph\n";

    std::cout << "\tCSetGraph adding edges:\n";
    timer.set_begin();
    CSetGraph graph2(graph_size);
    for (auto i : rand_verts) {
        graph2.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate();

    std::cout << "\t--Vertices count = " << graph2.vertices_count() << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from begin:\n";
    timer.set_begin();
    front_vertices = graph2.get_next_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph2.get_next_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from middle:\n";
    timer.set_begin();
    front_vertices = graph2.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph2.get_next_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from back:\n";
    timer.set_begin();
    front_vertices = graph2.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph2.get_next_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    ///////////////////////////////////////////////
    std::cout << "CArcGraph\n";

    std::cout << "\tCArcGraph adding edges:\n";
    timer.set_begin();
    CArcGraph graph3(graph_size);
    for (auto i : rand_verts) {
        graph3.add_edge(i.first, i.second);
    }
    timer.set_end();
    timer.calculate();

    std::cout << "\t--Vertices count = " << graph3.vertices_count() << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from begin:\n";
    timer.set_begin();
    front_vertices = graph3.get_next_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph3.get_next_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from middle:\n";
    timer.set_begin();
    front_vertices = graph3.get_next_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph3.get_next_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_next_vertices from back:\n";
    timer.set_begin();
    front_vertices = graph3.get_next_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        front_vertices = graph3.get_next_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);
    ///////////////////////////////////////////////

    std::cout << std::endl << "<========- CHECKING PREV VERTICES -========>" << std::endl;

    counter = 0;
    std::cout << "CListGraph" << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from begin:\n";
    timer.set_begin();
    std::vector<int> prev_vertices = graph.get_prev_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph.get_prev_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from middle:\n";
    timer.set_begin();
    prev_vertices = graph.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph.get_prev_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from back:\n";
    timer.set_begin();
    prev_vertices = graph.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph.get_prev_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    ///////////////////////////////////////////////
    std::cout << "CMatrixGraph" << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from begin:\n";
    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph1.get_prev_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from middle:\n";
    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph1.get_prev_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from back:\n";
    timer.set_begin();
    prev_vertices = graph1.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph1.get_prev_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    ///////////////////////////////////////////////
    std::cout << "CSetGraph" << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from begin:\n";
    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph2.get_prev_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from middle:\n";
    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph2.get_prev_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from back:\n";
    timer.set_begin();
    prev_vertices = graph2.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph2.get_prev_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);
    ///////////////////////////////////////////////
    std::cout << "CArcGraph" << std::endl;

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from begin:\n";
    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(0);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph3.get_prev_vertices(0);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from middle:\n";
    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(graph_size / 2);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph3.get_prev_vertices(graph_size / 2);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    //-----------------------------------------------
    std::cout << "\tget_prev_vertices from back:\n";
    timer.set_begin();
    prev_vertices = graph3.get_prev_vertices(graph_size - 1);
    timer.set_end();
    timer.calculate();

    timer.set_begin();
    for (size_t i = 0; i < rps_iter; ++i) {
        prev_vertices = graph3.get_prev_vertices(graph_size - 1);
    }
    timer.set_end();
    timer.check_rps(rps_iter);

    return 0;
}