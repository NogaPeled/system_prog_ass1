// Noga Peled
// nogapeled19@gmail.com

#include <iostream>
#include "UnionFind.hpp"

UnionFind::UnionFind(int n) // Constructor: Initializes 'n' elements, each in its own set.
{
    parent = new int[n];    
    rank = new int[n];
    size = n;
    
    // Initially, each element is its own parent (i.e., separate set)
    // and each set has rank 0 (a single node).
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
    
}

UnionFind::~UnionFind() // Destructor: Frees allocated memory for parent and rank arrays.
{
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int x) // Finds the representative (root) of the set containing x. Uses path compression to flatten the structure.
{
    if (x < 0 || x >= size) // Check for invalid index
    {
        throw std::out_of_range("Invalid index in find()");
    }

    if (parent[x] != x) // If x is not a root, compress path by pointing x to its root
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void UnionFind::unite(int x, int y) // Unites the sets containing x and y using union by rank. Smaller tree is attached under larger one to keep trees shallow.
{ 
    if (x < 0 || x >= size || y < 0 || y >= size) // Check for invalid index
    {
        throw std::out_of_range("Invalid index in unite()");
    }

    // Find roots of both sets
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return; // Already in the same set — no need to unite

    if (rank[rootX] < rank[rootY]) // Attach lower-rank tree under higher-rank tree
    {
        parent[rootX] =  rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
        parent[rootY] = rootX;
    }
    else
    {
        // Same rank — pick one to be root and increment its rank
        parent[rootY] = rootX;
        rank[rootX] = rank[rootX] + 1;
    }
    
}