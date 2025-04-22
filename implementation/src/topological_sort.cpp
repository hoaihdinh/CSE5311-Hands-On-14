#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <utility>

#include "depth_first_search.hpp"
#include "topological_sort.hpp"

bool cmp(const std::pair<char, int>& a, const std::pair<char, int>& b) {
    // the node that finishes first will be at the end of the list, node that finishes last is at the front
    return !(a.second < b.second); 
}

int topological_decoder(char n) {
    return n - 'm';
}

Graph* create_topological_graph() {
    Graph *topological_graph = new Graph(NUM_TOP_NODES, topological_decoder);
    
    topological_graph->add_edge('m', 'r');
    topological_graph->add_edge('m', 'q');
    topological_graph->add_edge('m', 'x');
    topological_graph->add_edge('n', 'q');
    topological_graph->add_edge('n', 'u');
    topological_graph->add_edge('n', 'o');
    topological_graph->add_edge('o', 'r');
    topological_graph->add_edge('o', 'v');
    topological_graph->add_edge('o', 's');
    topological_graph->add_edge('p', 'o');
    topological_graph->add_edge('p', 's');
    topological_graph->add_edge('p', 'z');
    topological_graph->add_edge('q', 't');
    topological_graph->add_edge('r', 'u');
    topological_graph->add_edge('r', 'y');
    topological_graph->add_edge('s', 'r');
    topological_graph->add_edge('u', 't');
    topological_graph->add_edge('v', 'x');
    topological_graph->add_edge('v', 'w');
    topological_graph->add_edge('w', 'z');
    topological_graph->add_edge('y', 'v');
    
    return topological_graph;
}

void topological_sort(Graph *graph, std::vector<char> &result) {
    int decode_diff = -1 * topological_decoder(0);

    int *end_times = dfs_algo(graph, topological_decoder, false);

    std::vector<std::pair<char, int>> vector_of_pairs;
    for(int i = 0; i < graph->get_node_count(); i++) {
        vector_of_pairs.push_back(std::pair<char, int>(i + decode_diff, end_times[i]));
    }

    std::sort(vector_of_pairs.begin(), vector_of_pairs.end(), cmp);

    for(int i = 0; i < graph->get_node_count(); i++) {
        result.push_back(vector_of_pairs[i].first);
    }
    delete end_times;
}