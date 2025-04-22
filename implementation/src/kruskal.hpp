#pragma once

#include "graph.hpp"

#define NUM_MST_NODES 9

int kruskal_decoder(char n);

Graph* create_kruskal_graph();

Graph* kruskal_mst(Graph* graph, std::function<int(char)> decoder);