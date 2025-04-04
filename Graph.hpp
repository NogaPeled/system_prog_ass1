#pragma once
#include <iostream>
 
namespace graph {

    /**
     * @brief Represents a single edge in the graph's adjacency list.
     */

    struct Edge {
        int dest_vertex; // The destination vertex this edge points to
        int weight;  // The weight of the edge
        Edge* next; // Pointer to the next edge in the adjacency list
    };

    /**
     * @brief Represents an undirected or directed graph using an adjacency list.
     */

    class Graph
    {

        private:
        int num_of_vertices; // Number of vertices in the graph
        Edge** adj_list; // Array of pointers to adjacency lists for each vertex

        public:

        /**
         * @brief Constructs a graph with a given number of vertices.
         * @param vertices The number of vertices in the graph.
         */

        Graph(int vertices); 

        /**
         * @brief Destructor to clean up dynamic memory used by the graph.
         */

        ~Graph(); 

        /**
         * @brief Adds an undirected edge between two vertices with an optional weight.
         * @param src_vertex Source vertex index.
         * @param dest_vertex Destination vertex index.
         * @param weight Weight of the edge (default is 1).
         * @throws std::out_of_range if any vertex index is invalid.
         */

        void addEdge(int src_vertex, int dest_vertex, int weight = 1);

         /**
         * @brief Adds a directed edge from src_vertex to dest_vertex with an optional weight.
         * @param src_vertex Source vertex index.
         * @param dest_vertex Destination vertex index.
         * @param weight Weight of the edge (default is 1).
         * @throws std::out_of_range if any vertex index is invalid.
         */

        void addDirectedEdge(int src_vertex, int dest_vertex, int weight = 1); 
        
        /**
         * @brief Removes an undirected edge between two vertices.
         * @param src_vertex One end of the edge.
         * @param dest_vertex The other end of the edge.
         * @throws std::out_of_range if vertex indices are invalid.
         * @throws std::runtime_error if the edge doesn't exist.
         */

        void removeEdge(int src_vertex, int dest_vertex);

        /**
         * @brief Prints the adjacency list representation of the graph.
         */

        void printGraph() const; 

        /**
         * @brief Returns the number of vertices in the graph.
         * @return Number of vertices.
         */

        int getNumOfVertices() const; 

        /**
         * @brief Returns the adjacency list of the graph.
         * @return A pointer to an array of adjacency lists.
         */

        Edge** getAdjList() const; 

        /**
         * @brief Returns the weight of the edge between two vertices.
         * @param src Source vertex.
         * @param dest Destination vertex.
         * @return Weight of the edge if it exists, INT_MAX otherwise.
         * @throws std::out_of_range if vertex indices are invalid.
         */

        int getWeight(int src, int dest) const;

    };

    /**
     * @brief Enum to represent the state of a vertex during traversal algorithms.
     */

    enum class VertexState
    {
        Unvisited, // Vertex has not been visited
        Visited, // Vertex is currently being explored
        Finished // Vertex and its descendants are fully explored
    };
}
