#pragma once
#include <iostream>
 
namespace graph {

    struct Edge {
        int dest_vertex;
        int weight;
        Edge* next;
    };

    class Graph
    {
        private:
        int num_of_vertices;
        Edge** adj_list; // A pointer to an array containing adjacency lists

        public:
        Graph(int vertices); // Constuctor to initialize the graph with a certain amout of vertices
        ~Graph(); // Destructor for the graph
        void addEdge(int src_vertex, int dest_vertex, int weight = 1); // Adds an edge to the graph
        void addDirectedEdge(int src_vertex, int dest_vertex, int weight = 1); // Adds a directed adge to a graph
        void removeEdge(int src_vertex, int dest_vertex); // Removes an edge from the graph
        void printGraph() const; // Prints a visuallization for the graph to the terminal
        int getNumOfVertices() const; // Returns the number of vetices in the graph
        Edge** getAdjList() const; // Returns the adjacency list
    };

    enum class VertexState
    {
        Unvisited,
        Visited,
        Finished
    };
}
