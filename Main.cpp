#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

using namespace graph;

int main() {
    // Create a graph with 6 vertices
    Graph g(6);

    // Add undirected edges
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5);

    std::cout << "Original Graph:\n";
    g.printGraph();

    std::cout << "\n--- BFS Tree ---\n";
    Graph bfs_tree = Algorithms::bfs(g, 0);
    bfs_tree.printGraph();

    std::cout << "\n--- DFS Tree ---\n";
    Graph dfs_tree = Algorithms::dfs(g, 0);
    dfs_tree.printGraph();

    std::cout << "\n--- Dijkstra (Shortest Paths from vertex 0) ---\n";
    Graph dijkstra_tree = Algorithms::dijkstra(g, 0);
    dijkstra_tree.printGraph();

    std::cout << "\n--- Prim's MST ---\n";
    Graph prim_tree = Algorithms::prim(g);
    prim_tree.printGraph();

    std::cout << "\n--- Kruskal's MST ---\n";
    Graph kruskal_tree = Algorithms::kruskal(g);
    kruskal_tree.printGraph();

    return 0;
}
