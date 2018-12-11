//
// Created by Kirill Smetankin on 10/12/2018.
//

#ifndef TP_1_SEM_IGRAPH_HPP
#define TP_1_SEM_IGRAPH_HPP

#include <vector>

struct IGraph {
    virtual ~IGraph() {}
    // Добавление ребра от from к to.
    virtual void add_edge(int from, int to) = 0;

    virtual size_t vertices_count() const = 0;

    virtual std::vector<int> get_next_vertices(int vertex) const = 0;
    virtual std::vector<int> get_prev_vertices(int vertex) const = 0;

};

#endif //TP_1_SEM_IGRAPH_HPP
