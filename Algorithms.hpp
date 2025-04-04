// Noga Peled
// nogapeled19@gmail.com

#pragma once
#include "Graph.hpp"

namespace graph {

    /**
     * @brief A utility class containing static graph algorithms such as BFS, DFS, Dijkstra, Prim, and Kruskal.
     * 
     * This class cannot be instantiated. All methods are static and operate on the Graph class.
     */

    class Algorithms 
    { 
        public:
        Algorithms() = delete; // Prevents instantiation of this utility class (static methods only)

        /**
         * @brief Performs Breadth-First Search (BFS) starting from a given vertex.
         * 
         * @param g The input graph (undirected).
         * @param start_vertex The vertex to begin the BFS traversal from.
         * @return A rooted tree as a directed graph representing the BFS traversal rooted at start_vertex.
         */

        static Graph bfs(const Graph& g, int start_vertex);

        /**
         * @brief Performs Depth-First Search (DFS) from a given start vertex.
         * 
         * If the graph is disconnected, DFS will cover all components (forest).
         * 
         * @param g The input graph.
         * @param start_vertex The starting vertex for the DFS traversal.
         * @return A directed graph representing the DFS tree or forest.
         */

        static Graph dfs(const Graph& g, int start_vertex);

        /**
         * @brief Helper function for performing a recursive DFS visit.
         * 
         * Marks vertices and builds the DFS tree as recursion progresses.
         * 
         * @param g The input graph.
         * @param current_vertex The vertex currently being visited.
         * @param vertex_state An array of states (Unvisited, Visited, Finished).
         * @param dfs_tree The tree/forest being constructed during DFS.
         */

        static void dfsVisit(const Graph& g, int current_vertex, VertexState* vertex_state, Graph& dfs_tree); 

        /**
         * @brief Computes the shortest path tree from a start vertex using Dijkstra's algorithm.
         * 
         * @param g The input graph.
         * @param start_vertex The source vertex.
         * @return A directed graph representing the shortest path tree.
         */

        static Graph dijkstra(const Graph& g, int start_vertex);

        /**
         * @brief Computes the Minimum Spanning Tree (MST) using Prim's algorithm.
         * 
         * Starts from vertex 0. Works on connected or disconnected graphs (returns a forest).
         * 
         * @param g The input graph.
         * @return An undirected graph representing the MST (or forest).
         */

        static Graph prim(const Graph& g);

        /**
         * @brief Computes the Minimum Spanning Tree (MST) using Kruskal's algorithm.
         * 
         * Uses Union-Find for cycle detection. Works on connected or disconnected graphs (returns a forest).
         * 
         * @param g The input graph.
         * @return An undirected graph representing the MST (or forest).
         */

        static Graph kruskal(const Graph& g);

    };
};