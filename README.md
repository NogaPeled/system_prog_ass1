
---

# System Programming - Assignment 1

## Overview
This project implements a graph data structure using an adjacency list and provides basic graph algorithms including:

- BFS (Breadth-First Search)
- DFS (Depth-First Search)
- Dijkstra's shortest paths algorithm
- Prim's Minimum Spanning Tree
- Kruskal's Minimum Spanning Tree

The implementation avoids use of the C++ STL (e.g., no `vector`, `queue`, `map`, etc.) and uses manually written data structures like queues and union-find, as required.

## Project Structure and Class Breakdown

### Core Files and Classes:

- **Graph.hpp / Graph.cpp**: Implements the `Graph` class using an adjacency list. Supports adding/removing undirected and directed edges, printing the graph, and accessing edge weights and adjacency lists.

- **Algorithms.hpp / Algorithms.cpp**: Contains static methods in the `Algorithms` class to perform graph traversal and pathfinding algorithms:
  - `bfs` – Breadth-first search
  - `dfs` – Depth-first search
  - `dijkstra` – Shortest paths from a source vertex
  - `prim` – Minimum spanning tree using Prim's algorithm
  - `kruskal` – Minimum spanning tree using Kruskal's algorithm

- **Queue.hpp / Queue.cpp**: Implements a basic circular queue class used for BFS traversal.

- **UnionFind.hpp / UnionFind.cpp**: Implements the Union-Find (Disjoint Set) data structure used for Kruskal’s algorithm, with path compression and union by rank.

- **Main.cpp**: Demonstrates the functionality of all implemented algorithms by creating a sample graph, running all algorithms, and printing results.

- **tests.cpp**: Contains automated test cases using the `doctest` framework to verify correctness of the graph structure, algorithms, queue, and union-find.

- **Makefile**: Handles compilation of both the main demo and test binaries, along with clean and valgrind targets.

- **doctest.h**: Header-only testing library used for unit testing.

## Build & Run

### Run the main demo:
```bash
Make main
```

### Run the demo:
```bash
./Main
```

### Run unit tests:
```bash
make test
```

### Clean build files:
```bash
make clean
```

### Check for memory leaks:
```bash
make valgrind
```

## Repository
You can find the project on GitHub here:
https://github.com/NogaPeled/system_prog_ass1.git

## Features Demonstrated in Main
The `Main.cpp` file constructs a graph of 6 vertices and runs all implemented algorithms, printing their resulting trees or path structures. Output includes:

- The original graph
- BFS tree starting from vertex 0
- DFS tree starting from vertex 0
- Dijkstra shortest path tree from vertex 0
- Minimum Spanning Tree using Prim
- Minimum Spanning Tree using Kruskal

## Notes
- All memory is managed manually (using `new`/`delete`) as STL containers are not allowed.
- Code has been tested with `doctest` and validated with `valgrind` for memory leaks.
- `addEdge` supports an optional weight parameter (default is 1).
- Input validation is included (e.g., throwing on invalid BFS or DFS start).

## dependencies
- Compiler: This project is compiled using g++.

## Contact

**Author**: Noga Peled  
**Email**: <nogapeled19@gmail.com>  


