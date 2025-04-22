#include <iostream>

#include "depth_first_search.hpp"
#include "topological_sort.hpp"
#include "kruskal.hpp"

int main() {
    std::cout << "===== DFS DEMO =====" << std::endl;
    Graph *dfs_graph = create_dfs_graph();
    dfs_graph->print_graph_matrix();
    dfs_graph->print_graph_list();

    int *dfs_result = dfs_algo(dfs_graph, dfs_decoder, true);
    delete dfs_result;

    std::cout << "===== TOPOLOGICAL SORT DEMO =====" << std::endl;
    Graph *topological_graph = create_topological_graph();
    topological_graph->print_graph_matrix();
    topological_graph->print_graph_list();

    std::vector<char> result;
    topological_sort(topological_graph, result);
    std::cout << "--- TOPOLOGICAL SORT RESULT" << std::endl;
    for(int i = 0; i < NUM_TOP_NODES; i++) {
        std::cout << result[i] << ((i == NUM_TOP_NODES-1) ? "" : ", ");
    }
    std::cout << "\n" << std::endl;

    std::cout << "===== KRUSKAL MST DEMO =====" << std::endl;
    Graph *kruskal_graph = create_kruskal_graph();
    kruskal_graph->print_graph_matrix();
    kruskal_graph->print_graph_list();

    Graph *mst_graph = kruskal_mst(kruskal_graph, kruskal_decoder);
    mst_graph->print_graph_matrix();
    mst_graph->print_graph_list();

    delete dfs_graph;
    delete topological_graph;
    delete kruskal_graph;
    delete mst_graph;
    return 0;
}