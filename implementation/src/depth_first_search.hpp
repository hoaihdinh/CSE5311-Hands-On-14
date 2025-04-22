#pragma once

#include "graph.hpp"

#define NUM_DFS_NODES 8

int dfs_decoder(char n);

Graph* create_dfs_graph();

int* dfs_algo(Graph* graph, std::function<int(char)> decoder, bool print_flag);