#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <set>
#include <vector>

#include "kruskal.hpp"

bool cmp_edge_costs(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
    // the node that finishes first will be at the end of the list, node that finishes last is at the front
    return std::get<2>(a) < std::get<2>(b); 
}

int kruskal_decoder(char n) {
    return n - 'a';
}

Graph* create_kruskal_graph() {
    Graph *kruskal_graph = new Graph(NUM_MST_NODES, kruskal_decoder);
    
    kruskal_graph->add_bi_dir_edge('a', 'b', 4);
    kruskal_graph->add_bi_dir_edge('a', 'h', 8);
    kruskal_graph->add_bi_dir_edge('b', 'h', 11);
    kruskal_graph->add_bi_dir_edge('b', 'c', 8);
    kruskal_graph->add_bi_dir_edge('c', 'i', 2);
    kruskal_graph->add_bi_dir_edge('c', 'f', 4);
    kruskal_graph->add_bi_dir_edge('c', 'd', 7);
    kruskal_graph->add_bi_dir_edge('d', 'f', 14);
    kruskal_graph->add_bi_dir_edge('d', 'e', 9);
    kruskal_graph->add_bi_dir_edge('e', 'f', 10);
    kruskal_graph->add_bi_dir_edge('f', 'g', 2);
    kruskal_graph->add_bi_dir_edge('g', 'h', 1);
    kruskal_graph->add_bi_dir_edge('g', 'i', 6);
    kruskal_graph->add_bi_dir_edge('h', 'i', 7);

    return kruskal_graph;
}

Graph* kruskal_mst(Graph *graph, std::function<int(char)> decoder) {
    int decode_diff = -1 * decoder(0);
    int num_nodes = graph->get_node_count();
    Graph *result = new Graph(num_nodes, decoder);

    std::vector<std::set<int>> sets;
    for(int i = 0; i < num_nodes; i++) {
        std::set<int> s = {i};
        sets.emplace_back(s);
    }

    std::vector<std::tuple<int, int, int>>* edges = graph->get_edges();
    std::sort(edges->begin(), edges->end(), cmp_edge_costs);

    for(int i = 0; i < edges->size(); i++) {
        int u = std::get<0>(edges->at(i));
        int v = std::get<1>(edges->at(i));
        if(sets[u].count(v) != 1) {
            result->add_bi_dir_edge(static_cast<char>(u+decode_diff), static_cast<char>(v+decode_diff), std::get<2>((*edges)[i]));
            sets[u].merge(sets[v]);
            sets[v] = sets[u];
        }
    }

    delete edges;
    return result;
}
