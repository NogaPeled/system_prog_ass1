#include "Graph.hpp"
#include <iostream>
#include <climits>

graph::Graph::Graph(int vertices) // Implementing a constructor for the graph
{
    num_of_vertices = vertices;
    adj_list = new Edge*[num_of_vertices]; // Dynamically allocates an array of size num_of_vertices,
    // Where each element is a pointer to the head of a linked list of edges (A list of pointers to Edge structs)
    for (int i = 0; i < num_of_vertices; i++)
    {
        adj_list[i] = nullptr; // Initiallizes each entry in the adjacency list to nullptr,
        // meaning "This vertex (adj_list[i]) currently has no neighbours"
    }

}

graph::Graph::~Graph() // Implementing a destructor for the graph
{
    for (int i = 0; i < num_of_vertices; i++)
    {
        Edge* current = adj_list[i];
        while (current != nullptr)
        {
            Edge* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adj_list;

}

void graph::Graph::addEdge(int src_vertex, int dest_vertex, int weight = 1)
{
    // Check if src_vertex, dest_vertex are within bounds
    if (src_vertex < 0 || src_vertex > num_of_vertices - 1 || dest_vertex < 0 || dest_vertex > num_of_vertices -1)
    {
        throw std::out_of_range("Invalid vertex index.");
    }
    
    // The graph is undirected, so we need to create an edge from src_vertex to dest_vertex and another edge from dest_vertex to src_vertex with the same weight
    // Create two Edge nodes (since the graph is undirected) and add each to the corresponding lists.

    Edge* src_to_dest = new Edge{dest_vertex, weight, adj_list[src_vertex]}; // Creates a new Edge node (to dest_vertex)
    // With a specific weight, and links it to the list of already existing neighbors of src_vertex
    adj_list[src_vertex] = src_to_dest; // Makes the new_edge the first neighbor in the list, concatenating the previous neighbors

    Edge* dest_to_src = new Edge{src_vertex, weight, adj_list[dest_vertex]}; // The opposite edge- from dest_vertex to src_vertex 
    adj_list[dest_vertex] = dest_to_src;

}

void graph::Graph::addDirectedEdge(int src_vertex, int dest_vertex, int weight = 1)
{
    if (src_vertex < 0 || src_vertex > num_of_vertices - 1 || dest_vertex < 0 || dest_vertex > num_of_vertices - 1)
    {
        throw std::out_of_range("Invalid vertex index.");
    }
    Edge* src_to_dest = new Edge{dest_vertex, weight, adj_list[src_vertex]};
    adj_list[src_vertex] = src_to_dest;
    
}

void graph::Graph::removeEdge(int src, int dest)
{
    // Check if src, dest are within bounds
    if (src < 0 || src > num_of_vertices - 1 || dest < 0 || dest > num_of_vertices -1)
    {
        throw std::out_of_range("Invalid vertex index.");
    }
    // Remove dest from src's list of neighbors
    Edge** current = &adj_list[src]; // A pointer to a pointer to the first neighbor of src
    while (*current && (*current)->dest_vertex != dest) // Go over src neighbors' list to find dest, while its not empty
    {
        current = &((*current)->next);
    }
    if (*current)
    {
        Edge* to_delete = (*current);
        *current = (*current)->next;
        delete to_delete;
    }
    else
    {
        throw std::runtime_error("The edge does not exist.");
    }

    current = &adj_list[dest]; // A pointer to a pointer to the first neighbor of dest
    while (*current && (*current)->dest_vertex != src) // Go over src neighbors' list to find dest, while its not empty
    {
        current = &((*current)->next);
    }
    if (*current)
    {
        Edge* to_delete = (*current);
        *current = (*current)->next; // Replace whats inside the pointer with the one after it- unlinks the "to_delete" node from the list
        delete to_delete;
    }
    else
    {
        throw std::runtime_error("The egde does not exist.");
    }

}

void graph::Graph::printGraph() const
{
    for (int i = 0; i < num_of_vertices; i++)
    {
        std::cout << "Vertex" << i << "->";
        Edge* current = adj_list[i];
        while (current)
        {
            std::cout << "[" << current->dest_vertex << ", weight = " << current->weight << "]";
            current = current->next;
        }
        std::cout << std::endl;
    }
    
}

int graph::Graph::getNumOfVertices() const
{
    return this->num_of_vertices;
}

graph::Edge** graph::Graph::getAdjList() const
{
    return this->adj_list;
}

int graph::Graph::getWeight(int src, int dest) const
{
    if (src < 0 || src >= num_of_vertices || dest < 0 || dest >= num_of_vertices)
    {
        throw std::out_of_range("Invalid vertex. ");
    }
    
    for (Edge* current = adj_list[src]; current != nullptr; current = current->next)
    {
        if (current->dest_vertex == dest)
        {
            return current->weight;
        }
        
    }

    return INT_MAX; // The edge doesnt exist, return infinity
    
}