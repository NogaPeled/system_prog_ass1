// Noga Peled
// nogapeled19@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include "Queue.hpp"
#include <stdexcept> // For exceptions
#include <climits>
#include "UnionFind.hpp"

graph::Graph graph::Algorithms::bfs(const Graph& g, int start_vertex)
{
    int num_vertices = g.getNumOfVertices();

    if (start_vertex < 0 || start_vertex >= num_vertices) // Bounds check
    {
        throw std::out_of_range("Invalid start vertex");
    }

    Graph rooted_tree(num_vertices); // The rooted tree to be returned drom the BFS traverse
    bool* visited = new bool[num_vertices]{false};
    
    Queue queue(num_vertices);
    queue.enqueue(start_vertex);
    visited[start_vertex] = true;

    while(!queue.isEmpty()) // Perform a breadth-first search on the graph, starting from "start_vertex"
    {
        int current = queue.dequeue();
        // std::cout << "Visited " << current << std::endl;

        for(Edge* edge = g.getAdjList()[current]; edge != nullptr; edge = edge->next) // Go over all the neighbors of "current", 
        // And check if they are already marked as visited. If not, mark them as visited (true) and add them to the queue
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

    if (start_vertex < 0 || start_vertex >= num_vertices) // Bounds check
    {
        throw std::out_of_range("Invalid start vertex");
    }

    Graph dfs_tree(num_vertices);
    VertexState* vertex_state = new VertexState[num_vertices]; // Dynamic array to store the state of visit of each vertex of the graph : Unvisited, Visited, Finished

    for (int i = 0; i < num_vertices; i++) // Initialize all vertices to Unvisited as default
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

graph::Graph graph::Algorithms::dijkstra(const Graph& g, int start_vertex)
{
    int num_vertices = g.getNumOfVertices();

    if (start_vertex < 0 || start_vertex >= num_vertices) // Bounds check
    {
        throw std::out_of_range("Invalid start vertex");
    }
    
    int* dist = new int[num_vertices]{INT_MAX}; // The shortest known distance from start_vertex to vertex i
    int* parent = new int[num_vertices]{-1}; // The previous vertex on the shortest path from start_vertex to i
    bool* visited = new bool[num_vertices]{false}; // Boolean value indicating whether vertex i has been fully processed (shortest distance is known)

    dist[start_vertex] = 0; // Distance from start_vertex to itself    

    // Main loop of dijkstra algorithm, process each vertex exactly once
    for (int count = 0; count < num_vertices - 1; count++)
    {
        int current = -1;
        int min_dist = INT_MAX;

        // Find the unvisited vertex with the minimum distance
        for (int i = 0; i < num_vertices; i++)
        {
            if (!visited[i] && dist[i] < min_dist)
            {
                min_dist = dist[i];
                current = i;
            }
            
        }

        if (current == -1) break; // All remaining vertices are inaccessible from source_vertex, break the loop

        visited[current] = true; // Mark the current vertex as visited

        // Relaxation step: update the distances to the adjacent vertices
        for (Edge* e = g.getAdjList()[current]; e != nullptr; e = e->next) // Update distances of adjacent vertices of the current vertex
        {
            int neighbor = e->dest_vertex;
            // Only update if the vertex has not been visited and the new distance is smaller
            if (!visited[neighbor] && dist[current] != INT_MAX && dist[current] + e->weight < dist[neighbor])
            {
                dist[neighbor] = dist[current] + e->weight;
                parent[neighbor] = current; // Update the parent to reconstruct the path later

            }
        }
    }

    // Constructing the shortest path tree as a graph from the parent array using getWeight() function to get the original edges' weight
    Graph shortest_tree(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        if (parent[i] != -1)
        {
            shortest_tree.addDirectedEdge(parent[i], i, g.getWeight(parent[i], i));
        }
    }

    // Clean resources
    delete[] dist;
    delete[] parent;
    delete[] visited;

    return shortest_tree;
    
}

graph::Graph graph::Algorithms::prim(const Graph& g)
{
    int num_vertices = g.getNumOfVertices(); 
    
    int* key = new int[num_vertices]{INT_MAX}; // The minumum weight edge that connects vertex i to the MST
    int* parent = new int[num_vertices]{-1}; // The parent of vertex i in the MST
    bool* inMST = new bool[num_vertices]{false}; // Boolean flag- is vertex i already included in the MST?

    key[0] = 0; // Start from vertex 0;
    
    for (int count = 0; count < num_vertices; count++) // Selects the minimum key vertex (minumum weight edge that connects vertex i to the MST) that is not yet in the MST
    {
        int current = -1;
        int min_key = INT_MAX;

        // Find a vertex that is not yet in the MST, with the smallest key value, and put it as our "current"
        for (int i = 0; i < num_vertices; i++)
        {
            if (!inMST[i] && key[i] < min_key)
            {
                min_key = key[i];
                current = i;
            }
            
        }

        if (current == -1) break; // All remaining vertices are inaccessible (like disconncted components), break the loop

        inMST[current] = true; // Mark the current vertex as included in the MST

        // Explore all neighbors of current vertex
        for (Edge* e = g.getAdjList()[current]; e != nullptr; e = e->next) // Update distances of adjacent vertices of the current vertex
        {
            int neighbor = e->dest_vertex; // dest_vertex is the neighbor of current
            int weight = e->weight;

            // if neighbor is not in MST and the edge current->neighbor has a lower weight than the current key[neighbor], update key[neighbor] to the new value 
            if (!inMST[neighbor] && weight < key[neighbor])
            {
                key[neighbor] = weight;
                parent[neighbor] = current; // Update the parent to reconstruct the path later
                // We plan to connect neighbor through current in the final MST
            }
        }

    }
    
    // Build MST using parent array
    Graph mst(num_vertices);
    for (int v = 0; v < num_vertices; v++)
    {
        if (parent[v] != -1)
        {
            mst.addEdge(parent[v], v, g.getWeight(parent[v], v));
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;

    return mst;
    
}

graph::Graph graph::Algorithms::kruskal(const Graph& g)
{
    int num_vertices = g.getNumOfVertices();
    Edge** adj = g.getAdjList(); // A pointer to an array of linked lists (one per vertex)

    // Local struct to hold edges temporarily
    struct KruskalEdge {
        int src;
        int dest;
        int weight;
    };

    // Estimate maximum number of unique edges (undirected, no duplicates) (n choose 2)
    int max_edges = num_vertices * (num_vertices - 1) / 2; // Max possible unique edges (undirected)

    // Allocate edge list
    KruskalEdge* edge_list = new KruskalEdge[max_edges];
    int edge_count = 0; 

    // Traverse adjacency list to extract unique edges (i < neighbor avoids duplicates)
    for (int i = 0; i < num_vertices; i++) // Loop through each vertex i
    {
        Edge* current = adj[i];
        while (current != nullptr) // Loop through i's neighbors using the linked list
        {
            int neighbor = current->dest_vertex;
            int weight = current->weight;
            if (i < neighbor) // If i < neighbor, store the edge (this avoids storing both (i,j) and (j,i))
            {
                edge_list[edge_count++] = {i, neighbor, weight};
            }
            current = current->next;
        }
        
    }

    // Sort the edges by weight using selection sort (sort the edge_list by weight)
    for (int i = 0; i < edge_count -  1; i++) // edge_count is the actual number of unique edges
    {
        int min_index = i;

        for (int j = i + 1; j < edge_count; j++)
        {
            if (edge_list[j].weight < edge_list[min_index].weight)
            {
                min_index = j;
            }
            
        }

        if (min_index != i)
        {
            KruskalEdge temp = edge_list[i];
            edge_list[i] = edge_list[min_index];
            edge_list[min_index] = temp;
        }
    }

    // Build mst using union find    
    Graph mst(num_vertices);
    UnionFind uf(num_vertices); 

    for (int i = 0; i < edge_count; i++)
    {
        int src = edge_list[i].src;
        int dest = edge_list[i].dest;
        int weight = edge_list[i].weight;

        // Only add edge if it connects two different sets (avoids cycles)
        if (uf.find(src) != uf.find(dest))
        {
            uf.unite(src, dest);
            mst.addEdge(src, dest, weight);
        }
        
    }
    
    delete[] edge_list;
    return mst;
}

