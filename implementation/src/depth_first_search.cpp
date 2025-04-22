#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "depth_first_search.hpp"

enum dfs_colors {
    white=0,
    gray=1,
    black=2
};

int dfs_decoder(char n) {
    return n - 'r';
}

Graph* create_dfs_graph() {
    Graph *dfs_graph = new Graph(NUM_DFS_NODES, dfs_decoder);
    
    dfs_graph->add_bi_dir_edge('r', 'v');
    dfs_graph->add_bi_dir_edge('r', 's');
    dfs_graph->add_bi_dir_edge('s', 'w');
    dfs_graph->add_bi_dir_edge('w', 't');
    dfs_graph->add_bi_dir_edge('w', 'x');
    dfs_graph->add_bi_dir_edge('t', 'x');
    dfs_graph->add_bi_dir_edge('t', 'u');
    dfs_graph->add_bi_dir_edge('u', 'x');
    dfs_graph->add_bi_dir_edge('x', 'y');

    return dfs_graph;
}

void dfs_visit(Graph* graph, int node, dfs_colors* colors, int* parents, int* start, int* end, int &step) {
    step += 1;
    start[node] = step;
    colors[node] = dfs_colors::gray;

    for(int i = 0; i < graph->get_node_count(); i++) {
        if(graph->get_edge(node, i) != 0 && colors[i] == dfs_colors::white) {
            parents[i] = node;
            dfs_visit(graph, i, colors, parents, start, end, step);
        }
    }
    colors[node] = dfs_colors::black;
    step += 1;
    end[node] = step;
}

int* dfs_algo(Graph* graph, std::function<int(char)> decoder, bool print_flag) {
    int decode_diff = -1 * decoder(0);
    int size = graph->get_node_count();
    dfs_colors *colors  = new dfs_colors[size];
    int *parents = new int[size];

    for(int i = 0; i < size; i++) {
        colors[i]  = dfs_colors::white;
        parents[i] = -1;
    }

    int *start = new int[size];
    int *end   = new int[size];
    int step = 0;
    for(int i = 0; i < size; i++) {
        if(colors[i] == dfs_colors::white) {
            dfs_visit(graph, i, colors, parents, start, end, step);
        }
    }

    if(print_flag) {
        std::cout << "--- DFS RESULT" << std::endl;
        std::cout << " node | discovered | complete | parent \n"
                  << "------+------------+----------+--------" << std::endl;
        for(int i = 0; i < size; i++) {
            char parent = (parents[i] != -1) ? parents[i] + decode_diff : '-';
            printf("%3c   |%6d      |%6d    |%4c    \n", i + decode_diff, start[i], end[i], parent);
        }
        std::cout << std::endl;
    }

    delete colors;
    delete parents;
    delete start;
    return end;
}