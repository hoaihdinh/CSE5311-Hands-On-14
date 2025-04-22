#pragma once

#include <vector>

#include "graph.hpp"

#define NUM_TOP_NODES 14

int topological_decoder(char n);

Graph* create_topological_graph();

void topological_sort(Graph *graph, std::vector<char> &result);