// Noga Peled
// nogapeled19@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "UnionFind.hpp"
#include <climits>
#include <sstream>

using namespace graph;

// Graph Tests 

TEST_CASE("Graph construction and vertex count") {
    Graph g(5);
    CHECK(g.getNumOfVertices() == 5);
}

TEST_CASE("Add undirected edge and get weight") {
    Graph g(3);
    g.addEdge(0, 1, 7);
    CHECK(g.getWeight(0, 1) == 7);
    CHECK(g.getWeight(1, 0) == 7);
}

TEST_CASE("Add directed edge and get weight") {
    Graph g(3);
    g.addDirectedEdge(1, 2, 9);
    CHECK(g.getWeight(1, 2) == 9);
    CHECK(g.getWeight(2, 1) == INT_MAX);
}

TEST_CASE("Remove edge") {
    Graph g(4);
    g.addEdge(0, 3, 5);
    g.removeEdge(0, 3);
    CHECK(g.getWeight(0, 3) == INT_MAX);
    CHECK(g.getWeight(3, 0) == INT_MAX);
}

TEST_CASE("Invalid edge operations") {
    Graph g(2);
    CHECK_THROWS_AS(g.addEdge(-1, 1), std::out_of_range);
    CHECK_THROWS_AS(g.removeEdge(0, 1), std::runtime_error);
}

TEST_CASE("Add self-loop edge") {
    Graph g(3);
    g.addEdge(1, 1, 4);
    CHECK(g.getWeight(1, 1) == 4);
}

TEST_CASE("Multiple edges overwrite previous") {
    Graph g(2);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 1, 5);  // Adds again (won't overwrite old one, both exist in list)
    CHECK(g.getWeight(0, 1) == 5);
}

TEST_CASE("Graph printGraph output") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 8);
    std::ostringstream buffer;
    std::streambuf* old_buf = std::cout.rdbuf(buffer.rdbuf());
    g.printGraph();
    std::cout.rdbuf(old_buf);

    std::string output = buffer.str();
    CHECK(output.find("Vertex 0") != std::string::npos);
    CHECK(output.find("[Vertex 1, weight = 5]") != std::string::npos);
    CHECK(output.find("[Vertex 2, weight = 8]") != std::string::npos);
}

TEST_CASE("Graph getAdjList basic check") {
    Graph g(2);
    g.addEdge(0, 1, 42);
    Edge** adj = g.getAdjList();
    CHECK(adj[0]->dest_vertex == 1);
    CHECK(adj[0]->weight == 42);
}

TEST_CASE("Graph getWeight invalid vertex") {
    Graph g(2);
    CHECK_THROWS_AS(g.getWeight(0, 5), std::out_of_range);
}

// Queue Tests 

TEST_CASE("Queue basic operations") {
    Queue q(3);
    CHECK(q.isEmpty());
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    CHECK(q.isFull());
    CHECK(q.peek() == 10);
    CHECK(q.dequeue() == 10);
    CHECK(!q.isFull());
    CHECK(!q.isEmpty());
    CHECK(q.dequeue() == 20);
    CHECK(q.dequeue() == 30);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue overflow and underflow") {
    Queue q(1);
    q.enqueue(42);
    CHECK_THROWS_AS(q.enqueue(99), std::overflow_error);
    q.dequeue();
    CHECK_THROWS_AS(q.dequeue(), std::underflow_error);
}

TEST_CASE("Queue with zero capacity") {
    CHECK_THROWS_AS(Queue(0).enqueue(1), std::overflow_error);
}

TEST_CASE("Queue capacity") {
    Queue q(5);
    CHECK(q.cap() == 5);
}

// UnionFind Tests 

TEST_CASE("UnionFind basic operations") {
    UnionFind uf(5);
    CHECK(uf.find(0) == 0);
    CHECK(uf.find(1) == 1);
    uf.unite(0, 1);
    CHECK(uf.find(0) == uf.find(1));
}

TEST_CASE("UnionFind multiple unions") {
    UnionFind uf(6);
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(1, 2);
    CHECK(uf.find(0) == uf.find(3));
    CHECK(uf.find(1) == uf.find(2));
}

TEST_CASE("UnionFind same node union") {
    UnionFind uf(3);
    uf.unite(1, 1);
    CHECK(uf.find(1) == 1);
}

TEST_CASE("UnionFind double union consistency") {
    UnionFind uf(3);
    uf.unite(0, 1);
    int root = uf.find(0);
    uf.unite(0, 1);
    CHECK(uf.find(1) == root);
}

TEST_CASE("UnionFind invalid index") {
    UnionFind uf(3);
    CHECK_THROWS_AS(uf.find(-1), std::out_of_range);
    CHECK_THROWS_AS(uf.find(3), std::out_of_range);
    CHECK_THROWS_AS(uf.unite(0, 3), std::out_of_range);
}

// Algorithms Tests 

TEST_CASE("BFS returns valid tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    Graph bfs_tree = Algorithms::bfs(g, 0);
    CHECK(bfs_tree.getWeight(0, 1) == 1);
    CHECK(bfs_tree.getWeight(1, 2) == 1);
    CHECK(bfs_tree.getWeight(2, 3) == 1);
}

TEST_CASE("BFS from invalid vertex") {
    Graph g(2);
    CHECK_THROWS_AS(Algorithms::bfs(g, 3), std::out_of_range);
}

TEST_CASE("DFS returns valid tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    Graph dfs_tree = Algorithms::dfs(g, 0);
    CHECK(dfs_tree.getNumOfVertices() == 4);
}

TEST_CASE("DFS from invalid vertex") {
    Graph g(2);
    CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::out_of_range);
}

TEST_CASE("Dijkstra on disconnected graph") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK(tree.getWeight(0, 1) == 5);
    CHECK(tree.getWeight(0, 2) == INT_MAX);
}

TEST_CASE("Prim on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);
    Graph mst = Algorithms::prim(g);
    CHECK(mst.getNumOfVertices() == 4);
}

TEST_CASE("Kruskal on disconnected graph") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getWeight(0, 1) == 1);
    CHECK(mst.getWeight(1, 2) == INT_MAX);
}

TEST_CASE("Prim minimum spanning tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    Graph mst = Algorithms::prim(g);
    CHECK(mst.getNumOfVertices() == 4);
}

TEST_CASE("Kruskal minimum spanning tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumOfVertices() == 4);
}