#include "Algorithms.hpp"
#include "Graph.hpp"
#include "Queue.hpp"
#include <stdexcept> // For exceptions

graph::Graph graph::Algorithms::bfs(const Graph& g, int start_vertex)
{
    int num_vertices = g.getNumOfVertices();
    Graph rooted_tree(num_vertices); // The rooted tree to be returned drom the BFS traverse
    bool* visited = nullptr;
    try
    {
        visited = new bool[num_vertices]{false};
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

        for(Edge* edge = g.getAdjList()[current]; edge != nullptr; edge = edge->next) // Go over all the neightbors of "current", 
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

graph::Graph graph::Algorithms::dfs(const Graph& g, int start_vertex)
{
    int num_vertices = g.getNumOfVertices();
    Graph dfs_tree(num_vertices);
    VertexState* vertex_state = nullptr;
    try
    {
        vertex_state = new VertexState[num_vertices];
    }
    catch(const std::bad_alloc e)
    {
        std::cerr << "Array allocation failed." << e.what() << std::endl;
        return dfs_tree;
    }

    for (int i = 0; i < num_vertices; i++)
    {
        vertex_state[i] = VertexState::Unvisited;
    }
    
    dfsVisit(g, start_vertex, vertex_state, dfs_tree);

    for (int i = 0; i < num_vertices; i++)
    {
        if (vertex_state[i] == VertexState::Unvisited)
        {
            dfsVisit(g, i, vertex_state, dfs_tree);
        }
        
    }
    
    delete[] vertex_state;
    return dfs_tree;

}

void graph::Algorithms::dfsVisit(const Graph& g, int current_vertex, VertexState* vertex_state, Graph& dfs_tree)
{
    vertex_state[current_vertex] = VertexState::Visited;

    for (Edge* edge = g.getAdjList()[current_vertex]; edge != nullptr; edge = edge->next)
    {
        int neighbor = edge->dest_vertex;
        if (vertex_state[neighbor] == VertexState::Unvisited) // If a neighbor is unvisited' it's a tree-edge and we add it to the dfs_tree
        {
            dfs_tree.addDirectedEdge(current_vertex, edge->dest_vertex);  
            dfsVisit(g, neighbor, vertex_state, dfs_tree); // Recursively go over the current vertex' neighbors
        }
        
    }

    vertex_state[current_vertex] = VertexState::Finished; 
}