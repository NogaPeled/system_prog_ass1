#include "Algorithms.hpp"
#include "Graph.hpp"
#include "Queue.hpp"
#include <stdexcept> // For exceptions

graph::Graph graph::Algorithms::bfs(const Graph& g, int start_vertex)
{
    int num_vertices = g.getNumOfVertices();
    Graph rooted_tree(num_vertices); // The rooted tree to be returned drom the BFS traverse
    bool* visited;
    try
    {
        bool* visited = new bool[num_vertices]{false};
    }
    catch(const std::bad_alloc e)
    {
        std::cerr << "Array allocation failed." << e.what() << std::endl;
    }
    
    Queue queue(num_vertices);
    queue.enqueue(start_vertex);
    visited[start_vertex] = true;

    while(!queue.isEmpty()) // Perform a bread first search on the graph, starting from "start_vertex"
    {
        int current = queue.dequeue();
        std::cout << "Visited " << current << std::endl;

        for(graph::Edge* edge = g.getAdjList()[current]; edge != nullptr; edge = edge->next) // Go over all the neightbors of "current", 
        // And check if they are already marked as visited. If not, mark them as true and add them to the queue
        {
            if (!visited[edge->dest_vertex])
            {
                visited[edge->dest_vertex] = true;
                queue.enqueue(edge->dest_vertex);
                rooted_tree.addDirectedEdge(current, edge->dest_vertex); // Add a new directed edge to the rooted tree
            }
        }
    }
    delete[] visited;
    return rooted_tree;

}