#pragma once
#include <iostream>

/**
 * @brief Disjoint Set Union (Union-Find) data structure.
 * Supports efficient find and unite operations with path compression and union by rank.
 */

class UnionFind {

    private:
    
    int* parent; // parent[i] points to the parent of element i (or itself if i is a root)
    int* rank; // rank[i] is a number assigned to each element i that represents an estimate of the depth of the tree rooted at i.
    int size; // Total number of elements (initially disjoint sets) managed by this Union-Find structure.
    /// Each element is represented by an index from 0 to size - 1.

    public:

    /**
     * @brief Constructs a UnionFind object with n elements (sets).
     * @param n Number of elements
     */

    UnionFind(int n);

    /**
     * @brief Destructor. Frees dynamically allocated memory.
     */

    ~UnionFind();

    /**
     * @brief Finds the representative (root) of the set containing x.
     * @param x The element to find
     * @return The root of x's set
     */

    int find(int x);

    /**
     * @brief Unites the sets containing x and y.
     * @param x First element
     * @param y Second element
     */

    void unite(int x, int y);

};