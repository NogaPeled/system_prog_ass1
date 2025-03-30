#pragma once
#include "Graph.hpp"

namespace graph {

    class Algorithms 
    { 
        public:
        Algorithms() = delete; // Prevents creation of objects **************************************

        // BFS algorithm : Returns a tree which is rooted at start_index, as a new graph
        static Graph bfs(const Graph& g, int start_vertex);

        // DFS algorithm : Returns a DFS tree or forest as a new graph
        static Graph dfs(const Graph& g, int start_vertex);

        // Dijkstra's algorithm : returns a shortest path tree from start_vertex as a new graph
        static Graph dijkstra(const Graph& g, int start_vertex);

        // Prim's algorithm : returns minumum spanning tree as a new graph
        static Graph prim(const Graph& g);

        // Kruskal's algorithm : returns minumum spanning tree as a new graph
        static Graph kruskal(const Graph& g);

    };
};